go
use Library
go

CREATE PROCEDURE Modify_type_column
AS
BEGIN
	Alter table Book
	Alter column Name varchar(100)
	PRINT('Name is varchar(100)')
	SELECT* FROM Book
END
CREATE PROCEDURE Modify_type_column_back
AS
BEGIN
	Alter table Book
	Alter column Name varchar(50)
	PRINT('Name is varchar(50) back')
	SELECT* FROM Book
END

CREATE PROCEDURE Add_column
AS 
BEGIN 
	Alter table Book
	Add Date_Published date
	PRINT('Column Date_Published added')
	SELECT* FROM Book
END

CREATE PROCEDURE Remove_column
AS 
BEGIN 
	Alter table Book
	Drop column Date_Published 
	PRINT('Column Date_Published removed')
	SELECT* FROM Book
END

CREATE PROCEDURE Add_Default 
AS
	BEGIN
		ALTER TABLE Book
		ADD CONSTRAINT df_Name DEFAULT ' ' FOR Name
		PRINT('Added " " as default Name')
	END
GO

CREATE PROCEDURE Remove_Default
AS
	BEGIN
		ALTER TABLE Book
		DROP CONSTRAINT df_Name
		PRINT('Removed default Name')
	END
GO

CREATE PROCEDURE Remove_PrimaryKey
AS
	BEGIN
		ALTER TABLE Book
		DROP CONSTRAINT pk_Book
		PRINT('Primary key was removed from Book')
	END
GO

CREATE PROCEDURE Add_PrimaryKey
AS
	BEGIN
		ALTER TABLE Book
		ADD CONSTRAINT pk_Book PRIMARY KEY(BID)
		PRINT('Primary key was added to Book')
	END
GO

CREATE PROCEDURE Add_CandidateKey
AS
	BEGIN
		ALTER TABLE Customer
		ADD CONSTRAINT c UNIQUE (Name)
		PRINT('Name form Costumer was made candidate key')
	END
GO


CREATE PROCEDURE Remove_CandidateKey
AS
	BEGIN
		ALTER TABLE Customer
		DROP CONSTRAINT c
		PRINT('Name is no longer candidate key')
	END
GO

CREATE PROCEDURE Add_ForeignKey
AS
	BEGIN
		ALTER TABLE Book
		ADD CONSTRAINT fk FOREIGN KEY(AID)
								REFERENCES Author(AID)
		PRINT('AID is foreign key referencing authors AID')
	END
GO

CREATE PROCEDURE Remove_ForeignKey
AS
	BEGIN
		ALTER TABLE Book
		DROP CONSTRAINT fk
		PRINT('AID removed foreign key')
	END
GO

CREATE PROCEDURE CreateTable
AS
BEGIN
		CREATE Table  NewTable(
		Col1 varchar(50) ,
		Col2 varchar(50),
		CONSTRAINT pk PRIMARY KEY (Col1))
		PRINT('NewTable was created')
	END
GO

CREATE PROCEDURE DropTable 
AS
	BEGIN
		DROP Table NewTable
		PRINT('NewTable was deleted')
	END
GO

CREATE Table KeepCurrentVersion (
	CurrentVersion int	
)
DELETE from KeepCurrentVersion
-- current version is the initial state:0
INSERT into KeepCurrentVersion VALUES (0)   


CREATE PROCEDURE PrintCurrentVersion
AS
	BEGIN
		DECLARE @Crt int
		SELECT @Crt=CurrentVersion
		FROM KeepCurrentVersion
		PRINT('Current version is: ' + CAST(@Crt as varchar(2)))
	END
GO

CREATE PROCEDURE DataBaseUpdate
AS
	DECLARE @currentVersion int
	SELECT @currentVersion = CurrentVersion FROM KeepCurrentVersion
	DECLARE @nextVersion int
	SET @nextVersion = @currentVersion+1
	DELETE from KeepCurrentVersion
	INSERT into KeepCurrentVersion VALUES (@nextVersion)

	if @currentVersion = 0
		exec Modify_type_column
	else if @currentVersion = 1
		exec Add_column
	else if @currentVersion = 2
		exec Add_Default
	else if @currentVersion = 3
		exec Remove_PrimaryKey
	else if @currentVersion = 4
		exec Add_CandidateKey
	else if @currentVersion = 5
		exec Add_ForeignKey
	else if @currentVersion = 6
		exec CreateTable
GO

CREATE PROCEDURE DataBaseUndo
AS
	DECLARE @cV int
	SELECT @cV = CurrentVersion FROM KeepCurrentVersion
	DECLARE @pV int
	SET @pV = @cV-1
	DELETE from KeepCurrentVersion
	INSERT into KeepCurrentVersion VALUES (@pV)

	if @cV = 1
		exec Modify_type_column_back
	else if @cV = 2
		exec Remove_column
	else if @cV = 3
		exec Remove_Default
	else if @cV = 4
		exec Add_PrimaryKey
	else if @cV = 5
		exec Remove_CandidateKey
	else if @cV = 6
		exec Remove_ForeignKey
	else if @cV = 7
		exec DropTable
GO

CREATE PROCEDURE GetToVersion(@GoalVersion int)
AS
	if @GoalVersion > 7 or @GoalVersion < 0
		RAISERROR ('Invalid version',10,1)
	
	else
	BEGIN
		DECLARE @CurrentVersion int
		SET @CurrentVersion = (SELECT CurrentVersion FROM KeepCurrentVersion)

		if @CurrentVersion = @GoalVersion
			PRINT('Currently in this version')

		while @GoalVersion > @CurrentVersion
			BEGIN
				exec DataBaseUpdate
				exec PrintCurrentVersion
				SET @CurrentVersion = (SELECT CurrentVersion FROM KeepCurrentVersion)
			END
		while @GoalVersion < @CurrentVersion
			BEGIN
				exec DataBaseUndo
				exec PrintCurrentVersion
				SET @CurrentVersion = (SELECT CurrentVersion FROM KeepCurrentVersion)
			END
	END
GO


exec GetToVersion 20
exec GetToVersion 0
exec GetToVersion 1
exec GetToVersion 2
exec GetToVersion 3
exec GetToVersion 4
exec GetToVersion 5
exec GetToVersion 6
exec GetToVersion 7

