#!/bin/sh
clear
# Start-Up for sdr-shell, dttsp, and usbsoftrock.  Oriented towards a Softrock
# RXTX board.
# http://sdr-shell.googlecode.com/svn/tags/PMSDR-1.0/sdr-shell.sh

set -x
export SDR_DEFRATE=96000 #48000 
DEV_CAPTURE=hw:1
DEV_PLAYBACK=hw:0

/usr/bin/jackd -R -P66 -p128 -t2000 -dalsa -r$SDR_DEFRATE -D -C$DEV_CAPTURE -P$DEV_PLAYBACK -s -p 2048&
# R - realtime
# P - realtime priority
# p - portmax (default 256)
# t - timeout(ms) - default 500
# d - driver
# r - alsa option: sample rate
# D - alsa option: duplex
# C - alsa option: capture if
# P - alsa option: playback if
# s - alsa option: softmode
# p - period: default 1024

# Realtime
#  rmmod capability
#  rmmod commoncap
#  modprobe realcap any=1 allcaps=1


JPID="$!"

sleep 2

export SDR_NAME=sdr
# prepare:
# mkfifo /dev/shm/SDRcommands
sdr-core -s -m&
PIDS="$PIDS $!"

sleep 1

# connect jack
#echo "  sdr-$DTTSP_PID:ol -> alsa_pcm:playback_1"
#$JACKC sdr-$DTTSP_PID:ol alsa_pcm:playback_1
#echo "  sdr-$DTTSP_PID:or -> alsa_pcm:playback_2"
#$JACKC sdr-$DTTSP_PID:or alsa_pcm:playback_2
#echo "  alsa_pcm:capture_1 -> sdr-$DTTSP_PID:il"
#$JACKC alsa_pcm:capture_1 sdr-$DTTSP_PID:il
#echo "  alsa_pcm:capture_2 -> sdr-$DTTSP_PID:ir"
#$JACKC alsa_pcm:capture_2 sdr-$DTTSP_PID:ir

jack_connect sdr:ol alsa_pcm:playback_1 
jack_connect sdr:or alsa_pcm:playback_2
jack_connect alsa_pcm:capture_1 sdr:il        
jack_connect alsa_pcm:capture_2 sdr:ir     
jack_lsp -c

export SDR_NAME=sdr-tx
export SDR_PARMPORT=19005
export SDR_SPECPORT=19006
export SDR_METERPORT=19007
# Path to DttSP command FIFO
export SDR_PARMPATH=/dev/shm/SDRcommands
# Path to DttSP meter FIFO
export SDR_METERPATH=/dev/shm/SDRmeter
# Path to DttSP spectrum FIFO
export SDR_SPECPATH=/dev/shm/SDRspectrum


sdr-core -s -m -v &
PIDS="$PIDS $!"
sleep 1

#tx stuff
#jack_lsp
#jack_connect sdr-tx:ol alsa_pcm:playback_3
#jack_connect sdr-tx:or alsa_pcm:playback_4
case $1 in
metronome )
	jack_metro -b 60 &
	PIDS="$PIDS $!"
	sleep 1
	jack_connect metro:60_bpm sdr-tx:il        
	jack_connect metro:60_bpm sdr-tx:ir
;;
* )
#tc stuff
#	jack_connect alsa_pcm:capture_3 sdr-tx:il
#	jack_connect alsa_pcm:capture_4 sdr-tx:ir
;;
esac

echo $PIDS

export SDR_MODE=$PWD/hook-mode
#export SDR_BAND=$PWD/hook-band
./sdr-shell

# kill jack clients before killing jack himself.
# this seems to be a cleaner shutdown than everything at once

kill $PIDS
sleep 2
kill $JPID
wait

