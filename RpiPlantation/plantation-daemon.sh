#!/bin/sh

NAME="plantation"
LOG_FACILITY="local3"
THIS_DIR=$(cd -- $(dirname "$BASH_SOURCE"); pwd)
PID_FILE="$THIS_DIR/$NAME.pid"

is_running () {
	[ -f "$PID_FILE" ] && [ -d "/proc/$(cat "$PID_FILE")" ]
}

start_plantation () {
	if is_running
		echo "$NAME already running!" >&2
		exit 1
	fi

	(
		cd -- "$THIS_DIR"
		(
			(nohup python3 ./RpiPlantation.py | logger -t "$NAME" -p "$LOG_FACILITY".info ) 2>&1
		) | logger -t "$NAME" -p "$LOG_FACILITY".err
	) &

	echo "$!" > "./$NAME.pid"
}

stop_plantation () {
	if ! is_running
		echo "$NAME is not running!" >&2
		exit 1
	fi

	kill $(cat "$PID_FILE")
}

status_plantation () {
	if is_running
		echo "$NAME is running" >&2
		return 0
	else
		echo "$NAME is stopped" >&2
		return 1
	fi
}

case "$1"
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
