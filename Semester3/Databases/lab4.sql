use Library
go

--tested tables
DBCC CHECKIDENT (Tables, RESEED, 0)
delete from Tables
insert into Tables values ('Author');--simple primary key with no foreign keys
insert into Tables values ('Most_Rented_Books');--simple primary key and a foreign key
insert into Tables values ('Book');--composite primary key
go
select *
from Tables
go

--tested views
DBCC CHECKIDENT (Views, RESEED, 0)
delete from Views
insert into Views values ('getBooks');				--single table
insert into Views values ('Books_Authors');		--join two tables
insert into Views values ('AuthorsCount');			--group by on two tables
--VIEWS

--get names of all books
go
create view getBooks as
select Name from Book
go
--books and authors

go
create view Books_Authors as
select b.Name,b.Date_Published from Book b
inner join Author a
on a.AID = b.AID;
go

--authors and how many books they have written
create view AuthorsCount as
select b.AID, b.Name, count(a.AID) as count
from Book b
inner join Author a
on b.AID=a.AID
group by b.AID, b.Name;
go
select * from Views
go

--tests
insert into Tests values ('10 values and all views');
insert into Tests values ('100 values and all views');
insert into Tests values ('200 values and single table view');
select* from Tests

--table tests
insert into TestTables values (1, 0, 10, 1);
insert into TestTables values (1, 1, 10, 2);
insert into TestTables values (1, 2, 10, 3);
insert into TestTables values (2, 0, 100, 1);
insert into TestTables values (2, 1, 100, 2);
insert into TestTables values (2, 2, 100, 3);
insert into TestTables values (3, 0, 200, 1);
insert into TestTables values (3, 1, 200, 2);
insert into TestTables values (3, 2, 200, 3);
select * from TestTables;

--view tests
insert into TestViews values (1, 0);
insert into TestViews values (1, 1);
insert into TestViews values (1, 2);
insert into TestViews values (2, 0);
insert into TestViews values (2, 1);
insert into TestViews values (2, 2);
insert into TestViews values (3, 0);
select * from TestViews;
go

drop procedure insert_into_author;
go
create procedure insert_into_author @entries int as
begin
	print 'inserting ' + convert(varchar(50), @entries) + ' into Author'
	while @entries > 0 begin
		insert into Author values (
			'Name ' + convert(varchar(10), @entries)
			)
		set @entries = @entries - 1
	end
end;

drop procedure insert_into_book;
go
create procedure insert_into_book @entries int as
begin
	print 'inserting ' + convert(varchar(50), @entries) + ' into Book'
	while @entries > 0 begin
		insert into Book(Name,TID,AID,PID) values(
			'Name ' + convert(varchar(10), @entries),
			@entries % 9+1,
			@entries % 9+1,
			@entries % 9+1
			)
		set @entries = @entries - 1
	end
end;

drop procedure insert_into_most
go
create procedure insert_into_most @entries int as
begin
	print 'inserting ' + convert(varchar(50), @entries) + ' into Most_Rented_Books'
	while @entries > 0 begin
		insert into Most_Rented_Books(BID,NrRentals) values(
			@entries % 9+1,
			@entries % 9+1
			)
		set @entries = @entries - 1
	end
end;

create table InsertOperations (
	table_name varchar(50),
	insert_procedure varchar(50)
);
delete from InsertOperations
insert into InsertOperations values ('Author', 'insert_into_author');
insert into InsertOperations values ('Employees', 'insert_into_book');
insert into InsertOperations values ('Counseling', 'insert_into_most');

select * from InsertOperations;

--execute the view with the given id
drop procedure execute_view_with_id;
go
create procedure execute_view_with_id @view_id int as
begin
	declare @start_time datetime
	declare @end_time datetime
	declare @view_name varchar(50)
	set @view_name = (select Name from Views where ViewID = @view_id)
	declare @query nvarchar(100)
	set @query = 'select * from ' + @view_name
	print 'executing view with id ' + convert(varchar(50), @view_id) + ': ' + @view_name
	set @start_time = getdate()
	execute sp_executesql @query
	set @end_time = getdate()
--
	declare @last_run_id int
	set @last_run_id = (select top 1 TestRunID from TestRuns order by TestRunID desc)
	insert into TestRunViews values (@last_run_id, @view_id, @start_time, @end_time)
end

--insert a number of records into a table with the given id
drop procedure insert_into_table_with_id;
go
create procedure insert_into_table_with_id @table_id int, @number_of_entries int as
begin
	declare @start_time datetime
	declare @end_time datetime
	declare @table_name varchar(50)
	declare @procedure_name varchar(50)
	set @table_name = (select Name from Tables where TableID = @table_id)
	set @procedure_name = (select iop.insert_procedure from InsertOperations iop where iop.table_name = @table_name)
	declare @query nvarchar(100)
	set @query = @procedure_name + ' ' + convert(varchar(50), @number_of_entries)
	print @procedure_name
--	print 'inserting ' + convert(varchar(50), @number_of_entries) + ' entries into table with id ' + convert(varchar(50), @table_id) + ': ' + @table_name
	set @start_time = getdate()
	execute sp_executesql @query
	set @end_time = getdate()
--
	declare @last_run_id int
	set @last_run_id = (select top 1 TestRunID from TestRuns order by TestRunID desc)
	insert into TestRunTables values (@last_run_id, @table_id, @start_time, @end_time)
end;

--delete all records from a table with the given id
--drop procedure delete_from_table_with_id;
go
create procedure delete_from_table_with_id @table_id int as
begin
	declare @table_name varchar(50)
	set @table_name = (select Name from Tables where TableID = @table_id)
	declare @query nvarchar(100)
	declare @id_column varchar(50)

	IF EXISTS (SELECT * from syscolumns where id = Object_ID(@TABLE_NAME) and colstat & 1 = 1)
		set @query = 'DBCC CHECKIDENT ('+ @table_name +', RESEED, 0); delete from ' + @table_name
	else
		set @query = 'delete from ' + @table_name
	print 'deleting all records from table with id ' + convert(varchar(10), @table_id) + ': ' + @table_name
	execute sp_executesql @query
end;
--procedure for running a test with the given id and name
drop procedure run_test;
go
create procedure run_test @test_id int, @test_name varchar(50) as
begin
	print 'running test with id ' + convert(varchar(10), @test_id) + ': ' + @test_name
	insert into TestRuns values (@test_name, NULL, NULL)
	declare @start_time datetime
	declare @end_time datetime
--
-- delete
--
	set @start_time = getdate()
	declare @number_of_tables_to_delete_left int
	declare @deleted_table_id int
	declare delete_table_cursor cursor for
		select TableID from TestTables where TestID = @test_id order by Position DESC
	open delete_table_cursor
--
	select @number_of_tables_to_delete_left = (select count(*) from TestTables where TestID = @test_id)
	print  'no. tables to delete ' + convert(varchar(10), @number_of_tables_to_delete_left );
	while @number_of_tables_to_delete_left > 0 begin
		fetch delete_table_cursor into @deleted_table_id
		print 'id' + convert(varchar(10), @deleted_table_id );
		execute delete_from_table_with_id @deleted_table_id
		set @number_of_tables_to_delete_left = @number_of_tables_to_delete_left - 1
	end
	--
	close delete_table_cursor
	deallocate delete_table_cursor
	--
--
-- insert
--
	declare @number_of_tables_to_insert_left int
	declare @insert_table_id int
	declare @insert_ammount int
	declare insert_table_cursor cursor for
		select TableID, NoOfRows from TestTables where TestID = @test_id order by Position ASC
	open insert_table_cursor
--
	select @number_of_tables_to_insert_left = (select count(*) from TestTables where TestID = @test_id)
--
	while @number_of_tables_to_insert_left > 0 begin
		fetch insert_table_cursor into @insert_table_id, @insert_ammount
		execute insert_into_table_with_id @insert_table_id, @insert_ammount
		set @number_of_tables_to_insert_left = @number_of_tables_to_insert_left - 1
	end
--
	close insert_table_cursor
	deallocate insert_table_cursor
--
-- views
--
	declare @number_of_views_left int
	declare @view_id int
	declare view_cursor cursor for
		select ViewID from TestViews where TestID = @test_id
	open view_cursor
--
	select @number_of_views_left = (select count(*) from TestViews where TestID = @test_id)
--
	while @number_of_views_left > 0 begin
		fetch view_cursor into @view_id
		print 'View id:' + convert(varchar(10), @view_id);
		execute execute_view_with_id @view_id
		set @number_of_views_left = @number_of_views_left - 1
	end
--
	close view_cursor
	deallocate view_cursor
--
	set @end_time = getdate()
--
	declare @last_run_id int
	set @last_run_id = (select top 1 TestRunID from TestRuns order by TestRunID desc)
	update TestRuns set
		StartAt = @start_time,
		EndAt = @end_time
	where TestRunID = @last_run_id
end;

execute run_all;;
go
drop procedure run_all;
go
create procedure run_all as begin
declare @no_tests_left int
	declare @test_id int
	declare @test_name varchar(50)
	declare test_cursor cursor
		for select TestID, Name
		from Tests
	open test_cursor
--
	select @no_tests_left = (select count(*) from Tests)
--
	while @no_tests_left > 0 begin
		fetch test_cursor into @test_id, @test_name
		print 'Running test ' + @test_name
		execute run_test @test_id, @test_name
		set @no_tests_left = @no_tests_left - 1
	end
--
	close test_cursor
	deallocate test_cursor
end;


delete from TestRuns
delete from TestRunTables
delete from TestRunViews
select * from TestRuns
go
select * from TestRunTables
go
select * from TestRunViews
go
