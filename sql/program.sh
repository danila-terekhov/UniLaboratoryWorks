#!/usr/bin/env bash
# vim: set expandtab shiftwidth=2 tabstop=2 :
cache_file=/tmp/kek

make_query(){
  echo "use lab;" > $cache_file
  echo "$1" >> $cache_file
  docker exec -i mysql sh -c 'exec mysql -uuser -puser 2>/dev/null ' < $cache_file
}

is_empty(){
login() {

make_query "select * from users;"
