#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cctype>

char *generateKey(int);
char encryptChar(char, char);
char decryptChar(char, char);
bool encryptFile(const char *, const char *, const char *);
bool decryptFile(const char *, const char *, const char *);

int main()
{
    std::srand(static_cast<unsigned>(std::time(0)));

    if (!encryptFile("input.txt", "encrypted.txt", "key.txt"))
    {
        std::cout << "Encryption failed.\n";
        return 1;
    }

    if (!decryptFile("encrypted.txt", "decrypted.txt", "key.txt"))
    {
        std::cout << "Decryption failed.\n";
        return 1;
    }

    std::cout << "Press Enter to exit...";
    std::cin.get();
    return 0;
}

char *generateKey(int length)
{
    if (length <= 0)
        return nullptr;

    char *key = new char[length + 1];
    for (int i = 0; i < length; ++i)
    {
        key[i] = 'A' + std::rand() % 26;
    }
    key[length] = '\0';
    return key;
}

char encryptChar(char plain, char keyChar)
{
    if (std::isalpha(static_cast<unsigned char>(plain)))
    {
        char base = std::isupper(static_cast<unsigned char>(plain)) ? 'A' : 'a';
        return (plain - base + (std::toupper(static_cast<unsigned char>(keyChar)) - 'A')) % 26 + base;
    }
    return plain;
}

char decryptChar(char cipher, char keyChar)
{
    if (std::isalpha(static_cast<unsigned char>(cipher)))
    {
        char base = std::isupper(static_cast<unsigned char>(cipher)) ? 'A' : 'a';
        return (cipher - base - (std::toupper(static_cast<unsigned char>(keyChar)) - 'A') + 26) % 26 + base;
    }
    return cipher;
}

bool encryptFile(const char *inputFile, const char *outputFile, const char *keyFile)
{
    std::ifstream fin(inputFile, std::ios::binary);
    if (!fin.is_open())
    {
        std::cout << "Error opening input file\n";
        return false;
    }

    fin.seekg(0, std::ios::end);
    const int length = static_cast<int>(fin.tellg());
    fin.seekg(0, std::ios::beg);

    /////// errors
    if (length <= 0)
    {
        std::cout << "Input file is empty\n";
        fin.close();
        return false;
    }

    char *content = new char[length];
    char *key = generateKey(length);
    if (!content || !key)
    {
        std::cout << "Memory allocation failed\n";
        delete[] content;
        delete[] key;
        fin.close();
        return false;
    }

    fin.read(content, length);
    if (!fin)
    {
        std::cout << "Error reading input file\n";
        delete[] content;
        delete[] key;
        fin.close();
        return false;
    }
    fin.close();

    std::ofstream fout(outputFile, std::ios::binary);
    std::ofstream fkey(keyFile, std::ios::binary);
    if (!fout.is_open() || !fkey.is_open())
    {
        std::cout << "Error creating output files\n";
        delete[] content;
        delete[] key;
        return false;
    }
    ///////

    for (int i = 0; i < length; ++i)
    {
        fout.put(encryptChar(content[i], key[i]));
    }
    fkey.write(key, length);

    delete[] content;
    delete[] key;
    fout.close();
    fkey.close();

    std::cout << "Encryption completed\n";
    return true;
}

bool decryptFile(const char *encryptedFile, const char *outputFile, const char *keyFile)
{
    std::ifstream fin(encryptedFile, std::ios::binary);
    /// errors
    if (!fin.is_open())
    {
        std::cout << "Error opening encrypted file\n";
        return false;
    }

    fin.seekg(0, std::ios::end);
    const int length = static_cast<int>(fin.tellg());
    fin.seekg(0, std::ios::beg);

    if (length <= 0)
    {
        std::cout << "Encrypted file is empty\n";
        fin.close();
        return false;
    }

    // allocates dynamic memory for key and decrypted file
    char *content = new char[length];
    char *key = new char[length];

    if (!content || !key)
    {
        std::cout << "Memory allocation failed\n";
        delete[] content;
        delete[] key;
        fin.close();
        return false;
    }

    fin.read(content, length);
    if (!fin)
    {
        std::cout << "Error reading encrypted file\n";
        delete[] content;
        delete[] key;
        fin.close();
        return false;
    }
    fin.close();
    

    std::ifstream fkey(keyFile, std::ios::binary);
    if (!fkey.is_open())
    {
        std::cout << "Error opening key file\n";
        delete[] content;
        delete[] key;
        return false;
    }

    fkey.read(key, length);
    if (fkey.gcount() != length)
    {
        std::cout << "Key size mismatch\n";
        delete[] content;
        delete[] key;
        fkey.close();
        return false;
    }
    fkey.close();

    std::ofstream fout(outputFile, std::ios::binary);
    if (!fout.is_open())
    {
        std::cout << "Error creating output file\n";
        delete[] content;
        delete[] key;
        return false;
    }

    for (int i = 0; i < length; ++i)
    {
        fout.put(decryptChar(content[i], key[i]));
    }

    delete[] content;
    delete[] key;
    fout.close();

    std::cout << "Decryption completed\n";
    return true;
}