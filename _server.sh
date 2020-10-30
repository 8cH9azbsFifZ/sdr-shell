#! /bin/bash
#
# sdr_02.sh
#
# Synopsis: 	The script starts jack, dttsp, connects the jack ports
#
# Version:      @(#)sdr.sh  v02  27-Aug-2006  ewpereira@gmail.com
#
# Author:	Edson Pereira, pu1jte, n1vtn
#
# Usage:        sdr_02.sh start|stop
#

##############################################################################
# Configure this to meet your environment

JACKD=/usr/bin/jackd
# For realtime use jackd in 2.6 kernels (KL7NA 8/03/07)
JACKDRT=/usr/bin/jackd
JACKC=/usr/bin/jack_connect
DTTSP=/usr/local/bin

##############################################################################
# Setup the environment
export SDR_DEFRATE=44100
export SND_DRIV="alsa"
# The following was added by Rob, KL7NA.
export SDR_PARMPATH="/dev/shm/SDRcommands"
export SDR_METERPATH="/dev/shm/SDRmeter"
export SDR_SPECPATH="/dev/shm/SDRspectrum"

##############################################################################
if [ "$SND_DRIV" == "oss" ]
then
/lib/oss/bin/./soundon
/lib/oss/bin/./ossmix -d1 envy24.ratelock OFF
/lib/oss/bin/./ossmix -d1 envy24.rate $SDR_DEFRATE
HOUT=/dev/dsp
HIN=/dev/dsp4
else 
if [ "$SND_DRIV" == "alsa" ]
then
ALSAH=hw:0
fi
fi

# Uncomment if your kernel has realtime capability
REALTIME=1


##############################################################################
# Test if we have the needed executables and directories
if [ ! -x $JACKD ]; then
  echo "Can't find $JACKD"
  exit 1
fi

if [ ! -d $DTTSP ]; then 
  echo "Can't find $DTTSP"
  exit 1
fi

if [ ! -x $JACKC ]; then
  echo "Can't find $JACKC"
  exit 1
fi

# If we have RT capability, get the realtime module ready
if [ $REALTIME ]; then
  echo "Configuring realtime module"
  JACKD="$JACKDRT -R"
# Modified for Fiesty lowlatency kernel (KL7NA 8/03/07)
#  rmmod capability
#  rmmod commoncap
#  modprobe realcap any=1 allcaps=1
fi
  
##############################################################################
case "$1" in
  start)  
    ##########################################################################
    # Create FIFOs if needed
    if [ ! -p $SDR_PARMPATH ]; then
       mkfifo -m a+rwx $SDR_PARMPATH
       ln -fs $SDR_PARMPATH /dev/shm/.SDRcommands
    fi

    if [ ! -p $SDR_METERPATH ]; then
       mkfifo -m a+rwx $SDR_METERPATH
       ln -fs $SDR_METERPATH /dev/shm/.SDRmeter
    fi

    if [ ! -p $SDR_SPECPATH ]; then
       mkfifo -m a+rwx $SDR_SPECPATH
       ln -fs $SDR_SPECPATH /dev/shm/.SDRspectrum
    fi
    
    ##########################################################################
    # Sanity check
    if [ ! -p $SDR_PARMPATH ]; then
       echo "Error while creating $SDR_PARMPATH fifo"
       exit 1
    fi

    if [ ! -p $SDR_METERPATH ]; then
       echo "Error while creating $SDR_METERPATH fifo"
       exit 1
    fi

    if [ ! -p $SDR_SPECPATH ]; then
       echo "Error while creating $SDR_SPECPATH fifo"
       exit 1
    fi
    
    ##########################################################################
    # Make sure jack and dttsp are not already running
    TMP=`ps -ef | grep jack | grep -v grep | wc -l`
    if [ ! $TMP == 0 ]; then
      echo "jackd is already running. Stopping..."
      exit 1
    fi

    TMP=`ps -ef | grep sdr-core | grep -v grep | wc -l`
    if [ ! $TMP == 0 ]; then
      echo "sdr-core is already running. Stopping..."
      exit 1
    fi

    ##########################################################################
    # Start jackd
    echo "> Starting jack..."
 
if [ "$SND_DRIV" == "oss" ]; then
   	$JACKD -d oss -P $HOUT -C $HIN -r $SDR_DEFRATE -p128 -n2 &
else
  if [ "$SND_DRIV" == "alsa" ]; then
	$JACKD -d alsa -d$ALSAH -r$SDR_DEFRATE -p1024 -n2 &
fi
fi


    JACKD_PID=$!
    if [ $JACKD_PID ] 
    then
      echo $JACKD_PID > ~/jackd.pid
      echo "  Succeeded. JackD PID is $JACKD_PID"
    else
      echo "  Failed"
      exit 1
    fi

    ##########################################################################
    # Needed in some systems
    sleep 1
    
    ##########################################################################
    # Start dttsp
    echo "> Starting dttsp..."
    $DTTSP/sdr-core -s -m &
    DTTSP_PID=$!
    JACKD_PID=$!
    if [ $DTTSP_PID ] 
    then
      echo $DTTSP_PID > ~/sdr-core.pid
      echo "  Succeeded. DttSP PID is $DTTSP_PID"
    else
      echo "  Failed"
      exit 1
    fi

    ##########################################################################
    # Connect the jack ports

if [ "$SND_DRIV" = "oss" ]; then
    echo "> Connecting dttsp to jack..."
    sleep 3 
    echo "  sdr-$DTTSP_PID:ol -> oss:playback_1"
    $JACKC sdr-$DTTSP_PID:ol oss:playback_1 
    echo "  sdr-$DTTSP_PID:or -> oss:playback_2"
    $JACKC sdr-$DTTSP_PID:or oss:playback_2 
    echo "  oss:capture_1 -> sdr-$DTTSP_PID:il"
    $JACKC oss:capture_1 sdr-$DTTSP_PID:il 
    echo "  oss:capture_2 -> sdr-$DTTSP_PID:ir"
    $JACKC oss:capture_2 sdr-$DTTSP_PID:ir 
else 
if [ "$SND_DRIV" = "alsa" ]; then
 echo "> Connecting dttsp to jack..."
    sleep 3 
echo "  sdr-$DTTSP_PID:ol -> alsa_pcm:playback_1"
    $JACKC sdr-$DTTSP_PID:ol alsa_pcm:playback_1
    echo "  sdr-$DTTSP_PID:or -> alsa_pcm:playback_2"
    $JACKC sdr-$DTTSP_PID:or alsa_pcm:playback_2
    echo "  alsa_pcm:capture_1 -> sdr-$DTTSP_PID:il"
    $JACKC alsa_pcm:capture_1 sdr-$DTTSP_PID:il
    echo "  alsa_pcm:capture_2 -> sdr-$DTTSP_PID:ir"
    $JACKC alsa_pcm:capture_2 sdr-$DTTSP_PID:ir
fi
fi

    ;;
  stop)
    JACKD_PID=`cat ~/sdr-core.pid`
    DTTSP_PID=`cat ~/jackd.pid`
    kill -9 $JACKD_PID $DTTSP_PID
    ;;
##############################################################################
# Give up
  *)
    echo "Usage: $0 {start|stop}" >&2
    exit 1
    ;;
esac
		
exit 0

