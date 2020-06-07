CREATE TABLE Accounts (
	id BIGINT PRIMARY KEY NOT NULL,
	familyName NVARCHAR(50) NOT NULL,
	creatableCharactersCount SMALLINT DEFAULT 10,
	createdDate DATETIME NOT NULL, 
	logoutDate DATETIME)
GO

CREATE TABLE Characters
	(characterId BIGINT IDENTITY(0,1) PRIMARY KEY,
	characterName NVARCHAR(50) UNIQUE NOT NULL,
	characterClass SMALLINT,
	level INT DEFAULT 1,
	exp FLOAT DEFAULT 0,
	currentHP BIGINT DEFAULT 100,
	currentMP BIGINT DEFAULT 100,
	maxHP BIGINT DEFAULT 100,
	maxMP BIGINT DEFAULT 100,	
	x FLOAT DEFAULT 140,
	y FLOAT DEFAULT 1,
	z FLOAT DEFAULT 20,
	rx FLOAT DEFAULT 0,
	ry FLOAT DEFAULT 0,
	rz FLOAT DEFAULT 0,
	location NVARCHAR(50) DEFAULT '벨리아 마을',
	accountId BIGINT NOT NULL,
	orderNum SMALLINT NOT NULL)
GO

CREATE OR ALTER PROC SearchAccount
@accountId BIGINT
AS
BEGIN
	SELECT familyName, creatableCharactersCount FROM dbo.Accounts 
		WHERE accountId = @accountId
END
GO

GRANT EXECUTE ON dbo.SearchAccount To poona
GO

CREATE OR ALTER PROC CreateAccount
@accountId BIGINT,
@familyName NVARCHAR(50)
AS
BEGIN
	DECLARE @count INT
	SELECT @count = COUNT(*) FROM dbo.Accounts 
		WHERE accountId = @accountId OR familyName = @familyName
	IF @count <> 0
		RETURN 0

	INSERT INTO dbo.Accounts (accountId, familyName, createdDate)
		VALUES (@accountId, @familyName, GETDATE())
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
	SELECT @count = COUNT(*) FROM dbo.Accounts WHERE accountId = @accountId
	IF @count = 0
		RETURN 0

	DELETE FROM dbo.Accounts WHERE accountId = @accountId
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
	SELECT
		characterId, characterName, characterClass,	
		level, exp, currentHP, currentMP, maxHP, maxMP,
		x, y, z, rx, ry, rz, location		
	FROM dbo.Characters 
	WHERE accountId = @accountId
	ORDER BY orderNum ASC
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
		SET orderNum = 
			CASE
				WHEN orderNum = @fromIndex THEN @toIndex
				ELSE @fromIndex 
			END
		WHERE accountId = @accountId AND orderNum in (@fromIndex, @toIndex) 
END
GO

GRANT EXECUTE ON dbo.GetCharacterList To poona
GO

CREATE OR ALTER PROC CreateCharacter
@accountId BIGINT,
@characterClass	SMALLINT,
@characterName NVARCHAR(50)
AS
BEGIN
	DECLARE @createdCharactersCount INT, @creatableCharactersCount INT
	SELECT @createdCharactersCount = COUNT(*) FROM dbo.Characters WHERE accountId = @accountId
	SELECT @creatableCharactersCount = creatableCharactersCount FROM dbo.Accounts WHERE accountId = @accountId
	IF @creatableCharactersCount = @createdCharactersCount
		RETURN 0

	INSERT INTO dbo.Characters (accountId, characterClass, characterName, orderNum)
		VALUES (@accountId, @characterClass, @characterName, @createdCharactersCount)
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
	DECLARE @deletedOrderNum BIGINT
	SELECT @deletedOrderNum = orderNum FROM dbo.Characters 
			WHERE characterId = @characterId

	DELETE FROM dbo.Characters WHERE characterId = @characterId
	IF @@ROWCOUNT = 0
		RETURN 0

	UPDATE dbo.Characters
		SET orderNum = orderNum - 1
		WHERE accountId = @accountId AND orderNum > @deletedOrderNum

	RETURN -1
END
GO

GRANT EXECUTE ON dbo.DeleteCharacter To poona
GO