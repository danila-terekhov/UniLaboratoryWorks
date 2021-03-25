#!/usr/bin/env bash
# vim: set expandtab shiftwidth=2 tabstop=2 :
cache_file=/tmp/kek
prmpt="What do you want? "
fzf_upd(){
  export FZF_DEFAULT_OPTS="--prompt='$prmpt' --inline-info --reverse --height 40%"
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
make_query "select mail, date, title from articles left join users on users.id = articles.writer_id" | less
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
add_new_subscription(){
  tput sc

  prmpt="Pls select writer "
  fzf_upd
  writer=$(make_query "select mail from users where role='writer'" | fzf)
  writer_id=$(make_query "select id from users where mail='$writer'")
  prmpt="Pls select reader "
  fzf_upd
  reader=$(make_query "select mail from users where role='reader'" | fzf)
  reader_id=$(make_query "select id from users where mail='$reader'")
 make_query "insert into subscriptions (writer_id, reader_id) values ('$writer_id', '$reader_id')"

  tput rc
  prmpt="$login "
  fzf_upd
}
show_all_subscriptions(){
make_query "select writer_id, reader_id, date from subscriptions" | fzf
}
select_articles_by_title(){
article=$(make_query "select title from articles" | fzf)
make_query "select content from articles where title='$article'"| sed -e "s//\n/" -e "s/\\\n//" | less
}
delete_my_article () {
article=$(make_query "select title from articles where writer_id=(select id from users where mail='$login')" | fzf)
make_query "delete from articles where title='$article'"
}
change_my_article(){
article=$(make_query "select title from articles where writer_id=(select id from users where mail='$login')" | fzf)
[[ -z $article ]] && return
tput sc
read -p "Enter new title: " title
echo  "Enter new content: C_d to stop"
content=$(cat)
make_query "update articles set title = '$title', content = '$content' where title='$article'"

}
work() {
  tmp=""

  tmp+="Show all articles\n" #2           [x]
  tmp+="Search article via price\n" #3.1  [x]
  tmp+="Search article via writer\n" #3.2 [x]
  tmp+="Add new subscription\n" #4        [x]
  tmp+="Show all subscriptions\n" #5      [x]
  tmp+="Select articles by title\n" #6    [x]
  tmp+="Change my article\n" #7.1         [x]
  tmp+="Delete my article\n" #7.2         [x]

  tmp+="logout\n"
  tmp+="exit"

  var=$(echo -e "$tmp" | fzf)
  case $var in
    Show\ all\ articles) show_all_articles ;;
    Search\ article\ via\ price) search_price ;;
    Search\ article\ via\ writer) search_writer ;;
    Add\ new\ subscription) add_new_subscription ;;
    Show\ all\ subscriptions) show_all_subscriptions ;;
    Select\ articles\ by\ title) select_articles_by_title ;;
    Delete\ my\ article) delete_my_article ;;
    Change\ my\ article) change_my_article ;;
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
