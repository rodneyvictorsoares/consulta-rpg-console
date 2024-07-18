CREATE DATABASE school_db

USE school_db

CREATE TABLE Cenario(
	id INT IDENTITY(1,1) NOT NULL,
	nome NVARCHAR(30) NOT NULL,
	descricao NVARCHAR(255),
	estilo NVARCHAR(20),
	CONSTRAINT PK_Cenario PRIMARY KEY (id)
)

INSERT INTO Cenario (nome, descricao, estilo)
	VALUES ('Greyhawk', 'Cenario de Alta fantasia baseada nos contos de Tolkien', 'Alta Fantasia'),
		   ('Raveloft', 'Cenario de terror medieval envolvendo classicos da literatura de horror, como vampiros, lobisomens, mumias e zumbis', 'Terror')