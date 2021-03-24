#!/usr/bin/env bash
# vim: set expandtab shiftwidth=2 tabstop=2 :
cache_file=/tmp/kek
prmpt="What do you want? "
fzf_upd(){
  export FZF_DEFAULT_OPTS="--prompt='$prmpt' --inline-info --reverse --height 10%"
}
fzf_upd

make_query(){
  echo "use lab;" > $cache_file
  echo "$1" >> $cache_file
  #docker exec -i mysql sh -c 'exec mysql -uuser -puser 2>/dev/null ' < $cache_file | tail -n+2
  echo 2
}
#make_query "select * from users;"


login() {
  var=$(echo -e "login\nregistrate\nexit" | fzf)
  tput sc
  case $var in
  login)
    read -p "Enter you login: " login
    read -sp "Enter you password: " password
    echo
    password=$(echo "$password" | md5sum | cut -c-32 )
    if [ $(make_query "select count(id) from users where email='$login' and password='$password'") -eq 1 ] ; then logged_in=1 ; fi
  ;;

  registrate)
    echo "You are creating a new account"
    read -p "Enter you login: " login
    read -sp "Enter you password: " password
    echo
    read -sp "Enter you password again: " password
    echo
    password=$(echo "$password" | md5sum | cut -c-32 )
    make_query "INSERT INTO 'users' ( 'role', 'mail', 'password', 'description') VALUES ('writer', '$login', '$password', NULL);"
    ;;
    exit) exit 0 ;;
  esac
  tput rc
}

work() {
  tmp="Add new article\n"
  tmp+="Add new subscription\n"
  tmp+="View all articles\n"
  tmp+="Search via titles\n"
  tmp+="exit"

  var=$(echo -e "$tmp" | fzf)
  case $var in
    exit) exit 0 ;;
  esac

}
main(){
  logged_in=0
  login
  while [[ $logged_in -ne 1 ]]; do
    if [ $var == "login" ] ; then
      prmpt="You are failed. "
      
    else
      prmpt="You are created new account. "
    fi
    fzf_upd
    login
  done
  prmpt="$login "
  fzf_upd

  while true; do
    work
  done

}
main
