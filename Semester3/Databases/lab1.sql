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
LID int primary key identity,Name varchar(50) )

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
 

--Lab2

INSERT INTO Type_book VALUES('SF')
INSERT INTO Type_book VALUES('Drama')
INSERT INTO Type_book VALUES('Romance')
SELECT* FROM Type_book

INSERT INTO Author VALUES('J.K Rowling')
INSERT INTO Author VALUES('Nicholas Sparks')
INSERT INTO Author VALUES('Jennifer Niven')
SELECT* FROM Author

INSERT INTO Publisher VALUES('Penguin')
INSERT INTO Publisher VALUES('Corint')
INSERT INTO Publisher VALUES('Humanitas')
SELECT* FROM Publisher

INSERT INTO Book(Name,TID,AID,PID) VALUES('Holding up the universe',1002,3,1)
INSERT INTO Book VALUES ('Dear John',1003,2,2)
INSERT INTO Book(Name,TID,AID,PID) VALUES('Harry Potter',1001,1,3)
INSERT INTO Book(Name,TID,AID,PID) VALUES('Sarah in Paris',1001,1,3)
INSERT INTO Book(Name,TID,AID,PID) VALUES('Arah in Paris',1001,1,3)
INSERT INTO Book(Name,TID,AID,PID) VALUES('Wrong',11,11,11)

SELECT* FROM Book

INSERT INTO Customer VALUES('Ana')
INSERT INTO Customer VALUES('Ionut')
INSERT INTO Customer VALUES('Lola')
INSERT INTO Customer VALUES('Ramo')
SELECT* FROM Customer

INSERT INTO Order_book VALUES(1006,2)
INSERT INTO Order_book VALUES(1008,1)
INSERT INTO Order_book VALUES(2002,1002)
SELECT* FROM Order_book

INSERT INTO Best_Customers VALUES(2,10)
INSERT INTO Best_Customers VALUES(1,10)
SELECT* FROM Best_Customers

INSERT INTO Most_Rented_Books VALUES(1006,3)
INSERT INTO Most_Rented_Books VALUES(2002,4)
INSERT INTO Most_Rented_Books VALUES(1008,15)
SELECT* FROM Most_Rented_Books
DELETE FROM Most_Rented_Books

INSERT INTO Librarian VALUES('Ana')
INSERT INTO Librarian VALUES('Mada')
SELECT* FROM Librarian

INSERT INTO Loan VALUES(1, 2,1007)
INSERT INTO Loan VALUES(2,1,1008)
INSERT INTO Loan VALUES(2,1002,1008)
SELECT* FROM Loan

UPDATE Book
SET Name='AAAA'
WHERE AID IN (12,3)
SELECT* FROM Book

UPDATE Best_Customers
SET Discount=20
WHERE CID>1
SELECT* FROM Best_Customers

UPDATE Customer
SET Name=''
WHERE CID IS NULL
SELECT* FROM Customer

UPDATE Book
SET Name='first'
WHERE AID BETWEEN 0 AND 1
SELECT* FROM Book

DELETE FROM Book
WHERE Name LIKE 'A%' 
SELECT* FROM Book

DELETE FROM Customer
WHERE Name = ''
SELECT* FROM Customer

SELECT Distinct B1.Name
FROM Book B1
WHERE Name LIKE 'H_%'
UNION
SELECT B2.Name
FROM Book B2
WHERE Name LIKE 'D_%'
ORDER BY Name

SELECT Distinct B1.Name
FROM Book B1
WHERE Name LIKE 'H_%' OR AID>1
ORDER BY Name

SELECT O.BID+2 as Bid
FROM Order_book O
WHERE CID >1 AND CID<3

SELECT* FROM Order_book

SELECT O.OID 
FROM Order_book O
WHERE CID >3 
INTERSECT 
SELECT O1.OID
FROM Order_book O1
WHERE BID >2

SELECT* FROM Order_book

SELECT Distinct B.Name
FROM Book B
WHERE PID = 3
EXCEPT
SELECT B1.Name
FROM Book B1
WHERE Name LIKE 'H%'

SELECT*
FROM Publisher p INNER JOIN Book B ON P.PID=B.PID 

INSERT INTO Author VALUES('T.J.Y')
SELECT*
FROM Author A LEFT OUTER JOIN Book B ON A.AID=B.AID

SELECT*
FROM Book B RIGHT OUTER JOIN Order_book O ON B.BID=O.BID
RIGHT OUTER JOIN Customer C ON C.CID=O.CID

SELECT* 
FROM Type_book T FULL OUTER JOIN Book B ON T.TID=B.TID
FULL OUTER JOIN  Author A ON A.AID=B.AID
FULL OUTER JOIN Publisher P ON P.PID= B.PID

SELECT TOP 1 B.Name, B.AID
FROM Book B
WHERE B.Name LIKE 'H%'and B.AID IN (SELECT A.AID
									FROM Author A)

SELECT B.Name, B.PID
FROM Book B
WHERE B.Name LIKE 'H%'and B.PID IN (SELECT P.PID
									FROM Publisher P
									WHERE P.Name LIKE 'H%'
									)
SELECT B.Name, B.PID+3 as PID
FROM Book B
WHERE B.Name LIKE 'H%'and EXISTS(SELECT* FROM Publisher P
									WHERE P.PID=B.PID
									)

SELECT B.Name, (B.TID+1)/2 as TID
FROM Book B
WHERE B.Name LIKE 'Ha%'and EXISTS(SELECT* FROM Type_book T
									WHERE T.TID=B.TID
									)
SELECT A.Name, A.TID
FROM(SELECT T.TID,T.Name
		FROM Type_book T INNER JOIN Book B ON T.TID=B.TID
		WHERE T.Name LIKE 'D%')A

SELECT A.Name, A.PID
FROM(SELECT P.PID,P.Name
		FROM Publisher P INNER JOIN Book B ON P.PID=B.PID
		WHERE P.Name LIKE 'P%')A

SELECT B.BESTID, AVG(B.Discount) AS AVERAGE
FROM Best_Customers B INNER JOIN Customer C ON B.CID=C.CID
GROUP BY B.BESTID

SELECT B.BESTID, AVG(B.Discount) AS AVERAGE
FROM Best_Customers B INNER JOIN Customer C ON B.CID=C.CID
GROUP BY B.BESTID
HAVING AVG(B.Discount) < 20

SELECT M.BID, MIN(M.NrRentals) AS MINIMUM
FROM Most_Rented_Books M INNER JOIN Book B ON B.BID=M.BID
GROUP BY M.BID

SELECT M.BID, MIN(M.NrRentals) AS MINIMUM
FROM Most_Rented_Books M INNER JOIN Book B ON B.BID=M.BID
GROUP BY M.BID
HAVING MIN(M.NrRentals)<10

SELECT L.LOANID, L.BID
FROM Loan L
WHERE L.BID >ALL(SELECT L1.BID FROM Loan L1
				WHERE L1.LOANID=L.LOANID)

SELECT L.LOANID, L.BID
FROM Loan L
WHERE L.BID >(SELECT MAX(L1.BID) FROM Loan L1
				WHERE L1.LOANID=L.LOANID)

SELECT O.OID,O.CID
FROM Order_book O
WHERE O.CID < ANY(SELECT O1.CID FROM Order_book O1
				WHERE O.OID=O1.OID)

SELECT O.OID,O.CID
FROM Order_book O
WHERE O.CID <(SELECT MIN(O1.CID) FROM Order_book O1
				WHERE O.OID=O1.OID)

SELECT L.LOANID, L.BID
FROM Loan L
WHERE L.BID <>ALL(SELECT L1.BID FROM Loan L1
				WHERE L1.LOANID=L.LOANID)

SELECT L.LOANID, L.BID
FROM Loan L
WHERE L.BID NOT IN(SELECT L1.BID FROM Loan L1
				WHERE L1.LOANID=L.LOANID)

SELECT O.OID,O.CID
FROM Order_book O
WHERE O.CID = ANY(SELECT O1.CID FROM Order_book O1
				WHERE O.OID=O1.OID)

SELECT O.OID,O.CID
FROM Order_book O
WHERE O.CID IN(SELECT O1.CID FROM Order_book O1
				WHERE O.OID=O1.OID)

