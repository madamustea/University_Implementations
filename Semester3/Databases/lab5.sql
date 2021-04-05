use Library
go
--create Ta,Tb,Tc
CREATE TABLE Ta ( 			
	aid INT PRIMARY KEY IDENTITY(1,1),  
	a2 INT NOT NULL UNIQUE 
)

CREATE TABLE Tb ( 
	bid INT PRIMARY KEY IDENTITY(1,1),  
	b2 INT 
)

CREATE TABLE Tc (
	cid INT PRIMARY KEY IDENTITY(1,1),			
	aid INT FOREIGN KEY REFERENCES Ta(aid),
	bid INT FOREIGN KEY REFERENCES tb(bid)   
)

drop table Ta
drop table Tb
drop table Tc

--inserts
insert into Ta values (1234),(4321),(4567),(7654),(9874),(4789),(5213)
insert into Tb values (30),(12),(16),(46),(8),(21),(61)
insert into Tc values (1,3),(2,1),(1,4),(4,2),(2,5),(3,1)

select * from Ta
select * from Tb
select * from Tc

-- a)
SET STATISTICS IO ON
--index scan
select Ta.aid
	from Ta
	order by Ta.aid
-- index seek
select Ta.aid 
	from Ta where Ta.aid = 4
-- index scan non clustered
select Ta.a2
	from Ta
	order by Ta.a2

-- index seek non clustered
select Ta.aid,Ta.a2
	from Ta
	where Ta.a2 = 5213

--b)

-- index seek non clustered
select Tb.b2
	from Tb where b2 = 21

-- clustered index scan
if exists (select name from sys.indexes where name = N'idx_b2')
	drop index idx_b2 on Tb;
go

--non clustered index seek
CREATE NONCLUSTERED INDEX idx_b2
ON Tb(b2)

--c.

GO
CREATE OR ALTER VIEW ViewThreeTables AS 
SELECT Ta.aid, Ta.a2, Tc.cid
FROM Tc  INNER JOIN Ta  ON Ta.aid = Tc.aid

--clustered index scan/seek
GO
SELECT * FROM ViewThreeTables

CREATE NONCLUSTERED INDEX idx_NC_I
ON Ta(a2) 
