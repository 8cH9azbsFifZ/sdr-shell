#!/bin/sh
clear
# Start-Up for sdr-shell, dttsp, and usbsoftrock.  Oriented towards a Softrock
# RXTX board.
# http://sdr-shell.googlecode.com/svn/tags/PMSDR-1.0/sdr-shell.sh
set -x
export SDR_DEFRATE=96000 #48000 
DEV_CAPTURE=hw:1
DEV_PLAYBACK=hw:0

## Start jackd
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
JPID="$!"
sleep 2

## Realtime
#rmmod capability
#rmmod commoncap
#modprobe realcap any=1 allcaps=1

## Start DttSP
export SDR_NAME=sdr
sdr-core --sprectrum --metering&
#/usr/local/bin/sdr-core --spectrum --metering --client-name=${NAME}_RX --buffsize=${JACK_BUFFER} --ringmult=4 --command-port=19001 --spectrum-port=19002 --meter-port=19003
PIDS="$PIDS $!"

sleep 1

# connect jack
jack_connect sdr:ol alsa_pcm:playback_1 
jack_connect sdr:or alsa_pcm:playback_2
jack_connect alsa_pcm:capture_1 sdr:il        
jack_connect alsa_pcm:capture_2 sdr:ir     
jack_lsp -c

export SDR_NAME=sdr-tx # double entry?
export SDR_PARMPORT=19005 # sdr-core eats this
export SDR_SPECPORT=19006  # sdr-core eats this
export SDR_METERPORT=19007  # sdr-core eats this

# FIFOs
export SDR_PARMPATH=/dev/shm/SDRcommands
export SDR_METERPATH=/dev/shm/SDRmeter
export SDR_SPECPATH=/dev/shm/SDRspectrum
# mkfifo /dev/shm/SDRcommands


sdr-core -s -m -v &
#/usr/local/bin/sdr-core --spectrum --metering --client-name=${NAME}_RX --buffsize=${JACK_BUFFER} --ringmult=4 --command-port=19001 --spectrum-port=19002 --meter-port=19003&

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

#export SDR_MODE=$PWD/hook-mode
#export SDR_BAND=$PWD/hook-band
./sdr-shell

# kill jack clients before killing jack himself.
# this seems to be a cleaner shutdown than everything at once

kill $PIDS
sleep 2
kill $JPID
wait

