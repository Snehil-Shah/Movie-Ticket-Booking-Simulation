create database CP_Project;

use CP_Project;

create table login (
login_id varchar(25) primary key,
cus_name varchar(20),
cus_email varchar(30),
pass_word varchar(15)
);

insert into login values('naman112','Naman Behl','naman034@gmail.com','csd@123#');
insert into login values('sup190','Snehil','snehil_1209@gmail.com','cse@123#');
insert into login values('gk113917','Gaurav Kumar','gaurav09kumar04@gmail.com','gk@123#');
insert into login values('ram1001','Ram','sharma.ram@gmail.com','ram@123#');


create table movies (
movie_id char(3) primary key,
movie_name varchar(50),
screen_no int,
bhasha varchar(10),
movie_veiwing_type char(2)
);

insert into movies values('B01','Pathaan',1,'Hindi','2D');
insert into movies values('B02','Drishyam 2',2,'Hindi','2D');
insert into movies values('B03','Gandhi Godse Ek Yudh',1,'Hindi','2D');
insert into movies values('B04','Faraaz',2,'Hindi','2D');
insert into movies values('H01','Avatar',4,'English','3D');
insert into movies values('H02','Avatar',3,'English','2D');
insert into movies values('H03','Puss in Boots',4,'English','3D');
insert into movies values('H04','Puss in Boots',3,'English','2D');
insert into movies values('H05','Avatar',1,'Hindi','2D');

create table price (
movie_id char(3),
movie_veiwing_type char(2),
seat_price int
);

insert into price values('B01','2D',300);
insert into price values('B02','2D',250);
insert into price values('B03','2D',250);
insert into price values('B04','2D',250);
insert into price values('H01','3D',450);
insert into price values('H02','2D',300);
insert into price values('H03','3D',400);
insert into price values('H04','2D',250);
insert into price values('H05','2D',300);


create table sys_admin (
admin_name varchar(20),
admin_pass varchar(20)
);

insert into sys_admin values('Snehil','6408');
insert into sys_admin values('Gaurav','2004');
insert into sys_admin values('Divyansh','2203');
insert into sys_admin values('Moksh','2221');

create database customer;
use customer;
create table base (ticket_id int PRIMARY KEY, movieid varchar(20), mall_name varchar(40), time varchar(20), seats int);