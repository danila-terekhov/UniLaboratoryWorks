#!/usr/bin/env bash
# vim: set expandtab shiftwidth=2 tabstop=2 :
cache_file=/tmp/kek
prmpt="What do you want? "
fzf_upd(){
  export FZF_DEFAULT_OPTS="--prompt='$prmpt' --inline-info --reverse --height 20%"
}
fzf_upd

make_query(){
  echo "use lab;" > $cache_file
  echo "$1" >> $cache_file
  docker exec -i mysql sh -c 'exec mysql -uuser -puser 2>/dev/null ' < $cache_file | tail -n+2

}

login() {
  var=$(echo -e "login\nregistrate\nexit" | fzf)
  tput sc
  case $var in
  login)
    read -p "Enter you login: " login
    read -sp "Enter you password: " password
    echo
    password=$(echo "$password" | md5sum | cut -c-32 )
    if [ $(make_query "select count(id) from users where mail='$login' and password='$password'") -eq 1 ] ; then logged_in=1 ; else prmpt="You are failed. " ; fi
  ;;

  registrate)
    echo "You are creating a new account"
    read -p "Enter you login: " login
    read -sp "Enter you password: " password
    echo
    read -sp "Enter you password again: "
    echo
    password=$(echo "$password" | md5sum | cut -c-32 )
    if [ $(make_query "select count(id) from users where mail='$login' ") -eq 1 ] ; then
    prmpt="User already exist. "
    else
    make_query "INSERT INTO users ( role, mail, password, description) VALUES ('writer', '$login', '$password', NULL);"
    prmpt="You are created new account. "
    fi
    ;;
    exit) exit 0 ;;
  esac
  tput rc
  fzf_upd
}

login_loop(){
  login
  while [[ $logged_in -ne 1 ]]; do
    login
  done
  prmpt="$login "
  fzf_upd
}
show_all_articles(){
make_query "select mail, date, title from articles join users on users.id = articles.writer_id" | less
}
search_writer(){
prmpt="Pls select writer "
fzf_upd

writer=$(make_query "select mail from users where role='writer'" | fzf)
make_query "select title from articles where writer_id=(select id from users where mail='$writer' )" | less
prmpt="$login "
fzf_upd
}
search_price(){
  tput sc
  read -p "Enter min price: " min
  read -p "Enter max price: " max
  tput rc
  if [[ $min -gt $max ]] ; then
    prmpt="Wrong numbers. "
  else
    make_query "select date, price, title from articles where price<=$max and price>=$min order by price desc" | less
  fi
  fzf_upd
}
work() {
  tmp=""

  tmp+="Show all articles\n" #2           [x]
  tmp+="Search article via price\n" #3.1  [x]
  tmp+="Search article via writer\n" #3.2 [x]
  tmp+="Add new subscription\n" #4        []
  tmp+="Show all subscriptions\n" #5      []
  tmp+="Filter articles by title\n" #6    []
  tmp+="Change my article\n" #7.1         []
  tmp+="Delete my article\n" #7.2         []
  tmp+="Add new article\n" #7.3           []

  tmp+="logout\n"
  tmp+="exit"

  var=$(echo -e "$tmp" | fzf)
  case $var in
    Show\ all\ articles) show_all_articles ;;
    Search\ article\ via\ price) search_price ;;
    Search\ article\ via\ writer) search_writer ;;
    logout) logged_in=0 ;;
    exit) exit 0 ;;
  esac

}
main(){
  logged_in=0
  login_loop

  while true; do
    work
    if [ "$var" == "logout" ] ; then
      prmpt="What do you want? "
      fzf_upd
      login_loop
    fi
  done

}
main
