#! /bin/sh
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

# Uncomment if your kernel has realtime capability
#REALTIME=1

# Which soundcard to use?
ALSAH=hw:0

##############################################################################
# Configure this to meet your environment

JACKD=/usr/bin/jackd
JACKDRT=/usr/bin/jackstart
JACKC=/usr/bin/jack_connect
DTTSP=/usr/local/sdr/dttsp/bin

##############################################################################
# Setup the environment
. $DTTSP/setup_env

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
  rmmod capability
  rmmod commoncap
  modprobe realcap any=1 allcaps=1
fi
  
##############################################################################
case "$1" in
  start)  
    ##########################################################################
    # Create FIFOs if needed
    if [ ! -p $SDR_PARMPATH ]; then
       mkfifo $SDR_PARMPATH
    fi

    if [ ! -p $SDR_METERPATH ]; then
       mkfifo $SDR_METERPATH
    fi

    if [ ! -p $SDR_SPECPATH ]; then
       mkfifo $SDR_SPECPATH
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
    $JACKD -dalsa -d$ALSAH -r$SDR_DEFRATE -p1024 -n2 &
    JACKD_PID=$!
    if [ $JACKD_PID ] 
    then
      echo $JACKD_PID > /var/run/jackd.pid
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
    cd $DTTSP
    $DTTSP/sdr-core -s -m &
    DTTSP_PID=$!
    JACKD_PID=$!
    if [ $DTTSP_PID ] 
    then
      echo $DTTSP_PID > /var/run/sdr-core.pid
      echo "  Succeeded. DttSP PID is $DTTSP_PID"
    else
      echo "  Failed"
      exit 1
    fi

    ##########################################################################
    # Connect the jack ports
    echo "> Connecting dttsp to jack..."
    sleep 1 
    echo "  sdr-$DTTSP_PID:ol -> alsa_pcm:playback_1"
    $JACKC sdr-$DTTSP_PID:ol alsa_pcm:playback_1
    echo "  sdr-$DTTSP_PID:or -> alsa_pcm:playback_2"
    $JACKC sdr-$DTTSP_PID:or alsa_pcm:playback_2
    echo "  alsa_pcm:capture_1 -> sdr-$DTTSP_PID:il"
    $JACKC alsa_pcm:capture_1 sdr-$DTTSP_PID:il
    echo "  alsa_pcm:capture_2 -> sdr-$DTTSP_PID:ir"
    $JACKC alsa_pcm:capture_2 sdr-$DTTSP_PID:ir
    ;;
  stop)
    JACKD_PID=`cat /var/run/sdr-core.pid`
    DTTSP_PID=`cat /var/run/jackd.pid`
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

