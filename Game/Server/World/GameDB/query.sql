-- 계정 테이블 생성
CREATE TABLE Accounts
	(accountId BIGINT IDENTITY(1, 1) PRIMARY KEY,
	id NVARCHAR(50) UNIQUE,
	password NVARCHAR(50) NOT NULL,	
	maxCreatableCharacters SMALLINT DEFAULT 10,
	createdCharacterCount SMALLINT DEFAULT 0,
	createdDate DATETIME NULL,
	logoutDate DATETIME NULL)
GO

-- 계정 데이터 넣기
CREATE OR ALTER PROC CreateAccount
@id NVARCHAR(50),
@password NVARCHAR(50)
AS
BEGIN
	DECLARE @count INT
	SELECT @count = COUNT(*) FROM dbo.Accounts WHERE id = @id
	IF @count <> 0
		RETURN 0

	INSERT INTO dbo.Accounts (id, password, createdDate, logoutDate)
	VALUES (@id, @password, GETDATE(), NULL)

	RETURN -1
END
GO

GRANT EXECUTE ON dbo.CreateAccount To poona
GO

-- 계정 조회
CREATE OR ALTER PROC SearchAccount
@id NVARCHAR(50),
@password NVARCHAR(50)
AS
BEGIN
	SELECT accountId FROM dbo.Accounts
	WHERE id = @id and password = @password
	IF @@ROWCOUNT = 0
		RETURN 0

	RETURN -1
END
GO

GRANT EXECUTE ON dbo.SearchAccount To poona
GO

CREATE TABLE CharacterInfo
	(characterId BIGINT IDENTITY(1,1) PRIMARY KEY,
	level INT DEFAULT 1,
	exp FLOAT DEFAULT 0,
	currentHP BIGINT DEFAULT 100,
	currentMP BIGINT DEFAULT 100,
	maxHP BIGINT DEFAULT 100,
	maxMP BIGINT DEFAULT 100,	
	x FLOAT DEFAULT 80,
	y FLOAT DEFAULT 22.5,
	z FLOAT DEFAULT 50,
	rx FLOAT DEFAULT 0,
	ry FLOAT DEFAULT 0,
	rz FLOAT DEFAULT 0,
	characterClass SMALLINT,
	familyName NVARCHAR(50) NOT NULL,
	characterName NVARCHAR(50) UNIQUE NOT NULL,
	location NVARCHAR(50) DEFAULT '벨리아 마을',
	accountId BIGINT NOT NULL)
GO

CREATE OR ALTER PROC CreateCharacter
@accountId BIGINT,
@characterClass	SMALLINT,
@characterName NVARCHAR(50)
AS
BEGIN
	DECLARE @count INT
	SELECT @count = COUNT(*) FROM dbo.CharacterInfo WHERE characterName = @characterName
	IF @count <> 0
		RETURN 0

	INSERT INTO dbo.CharacterInfo (characterClass, familyName, characterName, accountId)
	VALUES (@characterClass, 'Heroes', @characterName, @accountId)

	UPDATE dbo.Accounts 
	SET createdCharacterCount += 1
	WHERE accountId = @accountId

	RETURN -1
END
GO

GRANT EXECUTE ON dbo.CreateCharacter To poona
GO

CREATE OR ALTER PROC DeleteCharacter
@characterId BIGINT
AS
BEGIN
	UPDATE t1
	SET createdCharacterCount -= 1
	FROM dbo.Accounts AS t1
	LEFT JOIN dbo.CharacterInfo AS t2
	ON t1.accountId = t2.accountId
	WHERE t2.characterId = @characterId

	DELETE FROM dbo.CharacterInfo WHERE characterId = @characterId;	
	IF @@ROWCOUNT = 0
		RETURN 0

	RETURN -1
END
GO

GRANT EXECUTE ON dbo.DeleteCharacter To poona
GO

CREATE OR ALTER PROC SearchCharacterList
@accountId BIGINT
AS
BEGIN
	SELECT 
		A1.maxCreatableCharacters, A1.createdCharacterCount,
		A2.*  
	FROM dbo.Accounts A1
	FULL OUTER JOIN dbo.CharacterInfo A2
	ON A1.accountId = A2.accountId	
	WHERE A1.accountId = @accountId
	IF @@RowCount = 0
	BEGIN
		RETURN 0
	END

	RETURN -1
END
GO

GRANT EXECUTE ON dbo.SearchCharacterList To poona
GO

CREATE OR ALTER PROC SearchCharacter
@characterId BIGINT
AS
BEGIN
	SELECT * FROM dbo.CharacterInfo
	WHERE characterId = @characterId
	IF @@ROWCOUNT = 0
		RETURN 0

	RETURN -1
END
GO

GRANT EXECUTE ON dbo.SearchCharacter To poona
GO