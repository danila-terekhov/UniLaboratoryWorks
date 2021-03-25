-- Adminer 4.8.0 MySQL 8.0.23 dump

SET NAMES utf8;
SET time_zone = '+00:00';
SET foreign_key_checks = 0;
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

USE `lab`;

SET NAMES utf8mb4;

DROP TABLE IF EXISTS `articles`;
CREATE TABLE `articles` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `date` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `title` varchar(150) NOT NULL,
  `content` blob NOT NULL,
  `writer_id` int unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `writer_id` (`writer_id`),
  CONSTRAINT `articles_ibfk_1` FOREIGN KEY (`writer_id`) REFERENCES `articles` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


DROP TABLE IF EXISTS `subscriptions`;
CREATE TABLE `subscriptions` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `writer_id` int unsigned NOT NULL,
  `reader_id` int unsigned NOT NULL,
  `date` datetime DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `role` varchar(50) NOT NULL,
  `mail` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `description` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `users` (`id`, `role`, `mail`, `password`, `description`) VALUES
(1,	'writer',	'first@mail.com',	'09f831d11f4dbabcea21e2442c63a874',	'qwerty!1'),
(2,	'writer',	'second@mail.com',	'09f831d11f4dbabcea21e2442c63a874',	NULL),
(3,	'writer',	'third@mail.com',	'09f831d11f4dbabcea21e2442c63a874',	NULL),
(4,	'reader',	'first@mail.ru',	'6123ed2e27adda05c0b40ce00a99db71',	'qwerty2@'),
(5,	'reader',	'second@mail.ru',	'6123ed2e27adda05c0b40ce00a99db71',	'');

-- 2021-03-24 13:28:09
