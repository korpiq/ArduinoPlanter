#!/bin/bash

NAME="plantation"
LOG_FACILITY="local3"
THIS_DIR=$(cd -- $(dirname "$BASH_SOURCE"); pwd)
PID_FILE="$THIS_DIR/$NAME.pid"

is_running () {
	[ -f "$PID_FILE" ] && [ -d "/proc/$(cat "$PID_FILE")" ]
}

start_plantation () {
	if is_running
	then
		echo "$NAME already running!" >&2
		exit 1
	fi

	(
		cd -- "$THIS_DIR"
		LOG_CMD="logger -t $NAME -p $LOG_FACILITY"
		LOG_INFO="$LOG_CMD.info"
		LOG_ERR="$LOG_CMD.err"
		python3 ./RpiPlantation.py 1> >($LOG_INFO) 2> >($LOG_ERR) < /dev/null &
		echo "$!" > "./$NAME.pid"
	)
}

stop_plantation () {
	if ! is_running
	then
		echo "$NAME is not running!" >&2
		exit 1
	fi

	kill $(cat "$PID_FILE")
}

status_plantation () {
	if is_running
	then
		echo "$NAME is running" >&2
		return 0
	else
		echo "$NAME is stopped" >&2
		return 1
	fi
}

case "$1" in
	start)
		start_plantation
		;;
	stop)
		stop_plantation
		;;
	status)
		status_plantation
		exit $?
		;;
	*)
		echo "Usage: $0 [start|stop]" >&2
		exit 1
		;;
esac
