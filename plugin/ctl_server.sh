#! /bin/bash
ROOT_PATH=$(pwd)
BIN=${ROOT_PATH}/bin/serverd
LOG=${ROOT_PATH}/log/ctl_msg.log
CONF=${ROOT_PATH}/conf/server.conf
proc_name=$(basename $0)
function usage()
{
	printf "%s ./$proc_name [(start/-s)|(stop/-t)|(restart/-rs)|(status/-sa)]"
}
function print_log()
{
	local log_time=$(date +%Y_%m_%d:%H:%M:%S)
	local information=$1
	local level=$2
	echo "$log_time" "$information" "$level" 
}
function start_server()
{
	if check_server; then
		echo "server has already start..."
	    #print_log "server has already start..."
		print_log "server has already start..." "Notice"
	    return
    fi
	local ip=$(grep -E '^SERVERIP' $(CONF)|awk -F':' '{print $NF}')
	local port=$(grep -E '^PORT' $(CONF)| awk -F':' '{print $NF}' )
	${BIN} ${ip} ${port}
	if check_server; then
		echo "server start success..."
		print_log "server start success" "Notice"
	fi
}
function stop_server()
{
	if check_server;then
		local servername=$(basename ${BIN})
		local pid=${pidof $(servername)
	    kill -9 $pid
   else
       echo "server process has not exist"
	   print_log "stop ${servername} does not exist" "Notice"
	   return 
	fi
	if check_server; then  #check after call singal -9,isnot success? 
	   echo "stop success..."
	   print_log "stop ${servername} success" "Notice"
    else
		echo "stop failed"
		print_log "stop ${servername} failed" "Fatal"
    fi 
}
function restart_server()
{
		stop_server
		start_server
}
function status_server()
{
	if check_server; then
	   echo "this is server running..."
    fi
}
function check_server()
{
  local server_name=(basename $(BIN))
  local pid=$(pidof $(server_name))
  if [ ! -z "${pid}" ];then
	  return 0
  else 
	  return 1 #failed
  fi
}

 if [ $# -ne 1 ];then
	 print_log "you enter message is error" "Warning"
	 usage
	 exit 1
 fi
 case $1 in
	 'start'|'-s' )
	 start_server
	 ;;

	 'stop'|'-t' )
	 stop_server
	 ;;

     'restart'|'-rs')
	 restart_server
	 ;;

	 'status'|'sa')
	 status_server	
	 ;;

	 *)
	 ;;
 esac
