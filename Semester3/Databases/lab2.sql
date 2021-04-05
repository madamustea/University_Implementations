create database Library
go
use Library
go
create table Type_book(
TID int primary key identity, Name varchar(50))

create table Publisher(
PID int primary key identity,Name varchar(50))

create table Author(
AID int primary key identity,Name varchar(50))

create table Book(
BID int primary key identity,Name varchar(50),TID int foreign key references Type_book(TID),
AID int foreign key references Author(AID),PID int foreign key references Publisher(PID))

create table Librarian(
LID int primary key identity,Name varchar(50))

create table Customer(
CID int primary key identity,Name varchar(50))

create table Order_book(
OID int primary key identity NOT NULL,
BID int foreign key references Book(BID),CID int foreign key references Customer(CID))

create table Loan(LOANID int primary key identity,
LID int foreign key references Librarian(LID),CID int foreign key references Customer(CID),
BID int foreign key references Book(BID))

create table Most_Rented_Books(MOSTID int primary key identity,
BID int foreign key references Book(BID),NrRentals int)

create table Best_Customers(BESTID int primary key identity,
CID int foreign key references Customer(CID),Discount int)
 
 drop table Order_book
 drop table Loan
 drop table Most_Rented_Books
 drop table Best_Customers
