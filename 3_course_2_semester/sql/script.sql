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
  `date` datetime NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  `title` varchar(150) NOT NULL,
  `content` text NOT NULL,
  `writer_id` int unsigned DEFAULT NULL,
  `price` tinyint unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `writer_id` (`writer_id`),
  CONSTRAINT `articles_ibfk_14` FOREIGN KEY (`writer_id`) REFERENCES `users` (`id`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `articles` (`id`, `date`, `title`, `content`, `writer_id`, `price`) VALUES
(1,	'2021-03-25 10:25:16',	'Top news',	'abra cadabra\r\npam pam',	1,	101),
(4,	'2021-03-25 10:36:43',	'Title for 2 news',	'skdaksjdkjasdkfkjasdfkj',	4,	40),
(14,	'2021-03-25 13:12:13',	'AbraCadabra',	'CONTENT NEW ',	6,	19),
(15,	'2021-03-25 13:10:10',	'skjasdskjaskjd',	'qweqw',	6,	0);

DROP TABLE IF EXISTS `subscriptions`;
CREATE TABLE `subscriptions` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `writer_id` int unsigned NOT NULL,
  `reader_id` int unsigned NOT NULL,
  `date` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `subscriptions` (`id`, `writer_id`, `reader_id`, `date`) VALUES
(1,	2,	4,	'2021-03-25 11:52:35');

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
(4,	'reader',	'first@mail.ru',	'4cfdc2e157eefe6facb983b1d557b3a1',	'qwerty2@'),
(5,	'reader',	'second@mail.ru',	'6123ed2e27adda05c0b40ce00a99db71',	''),
(6,	'writer',	'qwe',	'dc829bf0d79e690c59cee708b527e6b7',	NULL);

-- 2021-03-25 13:13:07
