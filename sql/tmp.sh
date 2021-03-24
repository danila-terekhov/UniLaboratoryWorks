docker exec -i mysql sh -c 'exec mysql -uuser -puser 2>/dev/null ' < /tmp/kek  | tail -n+2 | cut -f 3 | fzf

#cat /tmp/kek
#use lab;
#select * from users;
