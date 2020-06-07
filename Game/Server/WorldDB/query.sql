CREATE TABLE Accounts (
	id BIGINT NOT NULL,
	familyName NVARCHAR(30) UNIQUE NOT NULL,
	creatableCharactersCount SMALLINT DEFAULT 10,
	createdDate DATETIME DEFAULT GETDATE(),
	loginDate DATETIME,
	logoutDate DATETIME,
	PRIMARY KEY(id)
)
GO

CREATE TABLE Characters (
	id BIGINT NOT NULL IDENTITY(0,1),
	accountId BIGINT NOT NULL,
	sortingOrder SMALLINT NOT NULL,
	"name" NVARCHAR(30) UNIQUE NOT NULL,
	classType SMALLINT,
	"level" INT DEFAULT 1,
	"exp" FLOAT DEFAULT 0,
	hp BIGINT NOT NULL,
	mp BIGINT NOT NULL,
	x FLOAT DEFAULT 140,
	y FLOAT DEFAULT 1.0,
	z FLOAT DEFAULT 20,
	rx FLOAT DEFAULT 0,
	ry FLOAT DEFAULT 0,
	rz FLOAT DEFAULT 0,
	"location" NVARCHAR(50) DEFAULT '벨리아 마을',
	PRIMARY KEY(id),
	CONSTRAINT FK_accountId_character 
		FOREIGN KEY (accountId) REFERENCES dbo.Accounts(id)
)
GO

CREATE OR ALTER PROC SearchAccount
@accountId BIGINT
AS
BEGIN
	SELECT familyName, creatableCharactersCount FROM dbo.Accounts 
		WHERE id = @accountId
END
GO

GRANT EXECUTE ON dbo.SearchAccount To poona
GO

CREATE OR ALTER PROC CreateAccount
@accountId BIGINT,
@familyName NVARCHAR(30)
AS
BEGIN
	DECLARE @count INT
	SELECT @count = COUNT(*) FROM dbo.Accounts 
		WHERE id = @accountId OR familyName = @familyName
	IF @count <> 0
		RETURN 0

	INSERT INTO dbo.Accounts (id, familyName)
		VALUES (@accountId, @familyName)
	IF @@ROWCOUNT = 0
		RETURN 0

	RETURN 1
END
GO

GRANT EXECUTE ON dbo.CreateAccount To poona
GO

CREATE OR ALTER PROC DeleteAccount
@accountId BIGINT
AS
BEGIN
	DECLARE @count INT
	SELECT @count = COUNT(*) FROM dbo.Accounts WHERE id = @accountId
	IF @count = 0
		RETURN 0

	DELETE FROM dbo.Accounts WHERE id = @accountId
	IF @@ROWCOUNT = 0
		RETURN 0

	RETURN 1
END
GO

GRANT EXECUTE ON dbo.DeleteAccount To poona
GO

CREATE OR ALTER PROC GetCharacterList
@accountId BIGINT
AS
BEGIN
	SELECT id, "name", classType, "level", "exp",
		hp, mp, x, y, z, rx, ry, rz, "location"	
	FROM dbo.Characters WHERE accountId = @accountId
	ORDER BY sortingOrder ASC
END
GO

GRANT EXECUTE ON dbo.GetCharacterList To poona
GO

CREATE OR ALTER PROC ChangeCharacterOrder
@accountId BIGINT,
@fromIndex SMALLINT,
@toIndex SMALLINT
AS
BEGIN
	UPDATE dbo.Characters 
		SET sortingOrder = 
			CASE
				WHEN sortingOrder = @fromIndex THEN @toIndex
				ELSE @fromIndex 
			END
		WHERE accountId = @accountId AND sortingOrder in (@fromIndex, @toIndex) 
END
GO

GRANT EXECUTE ON dbo.GetCharacterList To poona
GO

CREATE OR ALTER PROC CreateCharacter
@accountId BIGINT,
@classType	SMALLINT,
@characterName NVARCHAR(30),
@hp BIGINT,
@mp BIGINT
AS
BEGIN
	DECLARE @createdCharactersCount INT, @creatableCharactersCount INT
	SELECT @createdCharactersCount = COUNT(*) FROM dbo.Characters WHERE accountId = @accountId
	SELECT @creatableCharactersCount = creatableCharactersCount FROM dbo.Accounts WHERE id = @accountId
	IF @creatableCharactersCount = @createdCharactersCount
		RETURN 0

	INSERT INTO dbo.Characters (accountId, sortingOrder, classType, "name", hp, mp)
		VALUES (@accountId, @createdCharactersCount, @classType, @characterName, @hp, @mp)
	IF @@ROWCOUNT = 0
		RETURN 0

	RETURN -1
END
GO

GRANT EXECUTE ON dbo.CreateCharacter To poona
GO

CREATE OR ALTER PROC DeleteCharacter
@accountId BIGINT,
@characterId BIGINT
AS
BEGIN
	DECLARE @deletedOrder BIGINT
	SELECT @deletedOrder = sortingOrder FROM dbo.Characters 
			WHERE sortingOrder = @characterId

	DELETE FROM dbo.Characters WHERE id = @characterId
	IF @@ROWCOUNT = 0
		RETURN 0

	UPDATE dbo.Characters
		SET sortingOrder = sortingOrder - 1
		WHERE accountId = @accountId AND sortingOrder > @deletedOrder

	RETURN -1
END
GO

GRANT EXECUTE ON dbo.DeleteCharacter To poona
GO

CREATE OR ALTER PROC UpdateCharacterStatus
@accountId BIGINT,
@characterId BIGINT,
@level INT,
@exp FLOAT,
@hp BIGINT,	
@mp BIGINT,	
@x FLOAT,
@y FLOAT,
@z FLOAT,
@rx FLOAT,
@ry FLOAT,
@rz FLOAT,
@location NVARCHAR(50)
AS
BEGIN
	UPDATE dbo.Characters 
		SET "level" = @level,
			"exp" = @exp,
			hp = @hp,
			mp = @mp,
			x = @x, y = @y, z = @z,
			rx = @rx, ry = @ry, rz = @rz,
			"location" = @location
		WHERE accountId = @accountId AND id = @characterId
END
GO