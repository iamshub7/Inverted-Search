Inverted_Search_Project (Data Structures)

📌 Description
This project implements an inverted index search system in C. It reads multiple text files, creates a database of words with occurrences across files using a hash table with linked lists, and allows fast word-based searches. The project demonstrates file handling, string manipulation, dynamic memory allocation, and linked data structures.

The database supports adding new files, searching for word occurrences, displaying the database, and saving/loading it from a file.

⚙️ Features

Hash table-based word indexing (27 buckets: a-z + numbers/specials)

Linked lists for multiple files per word

Case-insensitive word handling

Add, update, and save database functionality

Search for a word and list all files containing it with counts

Modular and well-structured C code

🛠 Technologies Used

Language: C

Concepts: File handling, Strings, Linked lists, Hash tables, Dynamic memory allocation, Pointers & structures

Platform: Linux

Compiler: GCC

📂 Project Structure

PROJECT - 1 Inverted_Search/
├── create.c        # Database creation logic
├── display.c       # Display database
├── main.c          # Main program & menu
├── main.h          # Header file with data structures and function prototypes
├── save.c          # Save database to file
├── search.c        # Search words in database
├── update.c        # Update database from file
├── validate.c      # Validate input files
└── README.md       # Project documentation


▶️ Usage

Create Database: Run the program and choose option 1, providing text files as command-line arguments.

Search Word: Option 2 in menu to search word across files.

Display Database: Option 3 to view entire word-to-file mapping.

Update Database: Option 4 to add data from saved database files.

Save Database: Option 5 to save current database to a .txt file.

📚 Learning Outcomes

Understanding inverted index and word-based searching

Implementing hash tables with linked lists

File handling and parsing in C

Memory management with dynamic allocation and pointers

Modular C programming for maintainable code

Building simple command-line interfaces

🚧 Limitations

Supports only text-based files

Case-insensitive only for first character

Special characters/numbers handled in a single bucket

Designed for educational purposes, not optimized for very large datasets

👨‍💻 Author
Shubham Shinde

📜 License
This project is open-source and intended for educational and learning purposes.
