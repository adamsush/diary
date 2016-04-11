-- Persons table
CREATE TABLE Person (
    id INTEGER PRIMARY KEY,
    name TEXT
);

CREATE INDEX PersonIndex ON Person(id);

-- Books table
CREATE TABLE Book (
    id INTEGER PRIMARY KEY,
    name TEXT,
    person_id INTEGER,
    FOREIGN KEY(person_id) REFERENCES Person(id)
);

CREATE INDEX BookIndex ON Book(id);

-- Task table
CREATE TABLE Task (
    id INTEGER PRIMARY KEY,
    name TEXT,
    description TEXT,
    task_date TEXT,
    task_time TEXT,
    status INTEGER,    -- 0 - in progress, 1 - closed
    deleted INTEGER,   -- 0 - NO, 1 - YES
    comment TEXT,
    book_id INTEGER,
    FOREIGN KEY(book_id) REFERENCES Book(id)
);

CREATE INDEX TaskIndex ON Task(id);

-- Note table
CREATE TABLE Note (
    id INTEGER PRIMARY KEY,
    data TEXT,
    book_id INTEGER,
    FOREIGN KEY(book_id) REFERENCES Book(id)
);

CREATE INDEX NoteIndex ON Note(id);

-- Addressbook table
CREATE TABLE Addressbook (
    id INTEGER PRIMARY KEY,
    name1 TEXT,
    name2 TEXT,
    birthday TEXT,
    phone_id INTEGER,
    address TEXT,
    comment TEXT,
    book_id INTEGER,
    email_id INTEGER,
    FOREIGN KEY(book_id) REFERENCES Book(id)
);

CREATE INDEX AddressbookIndex ON Addressbook(id);

-- Phonebook table
CREATE TABLE Phonebook (
    id INTEGER PRIMARY KEY,
    phone TEXT,
    comment TEXT,
    type TEXT,
    book_id INTEGER,
    addr_id INTEGER,
    FOREIGN KEY(book_id) REFERENCES Book(id),
    FOREIGN KEY(addr_id) REFERENCES Addressbook(id)
);

CREATE INDEX PhonebookIndex ON Phonebook(id);

-- Email table
CREATE TABLE Email (
    id INTEGER PRIMARY KEY,
    data TEXT,
    comment TEXT,
    book_id INTEGER,
    addr_id INTEGER,
    FOREIGN KEY(book_id) REFERENCES Book(id),
    FOREIGN KEY(addr_id) REFERENCES Addressbook(id)
);

CREATE INDEX EmailIndex ON Email(id);

-- Initialization of tables
INSERT INTO Person (name) VALUES ("default");
INSERT INTO Book (name, person_id) VALUES ("default", 1);
