#!/usr/bin/env bash


[[ -n `docker ps | grep mysql` ]] || docker run -d --name mysql  -e MYSQL_ROOT_PASSWORD=root -p 3306:3306 -e MYSQL_DATABASE=lab -e MYSQL_USER=user -e MYSQL_PASSWORD=user mysql --default-authentication-plugin=mysql_native_password && docker exec mysql mysql -uuser -puser < script.sql

