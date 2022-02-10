#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#ifdef _WIN32
string command = "dir /A-D /B > temp.txt";
#endif
#ifdef linux
string command = "ls -A1 > temp.txt";
#endif

vector<string> generateFileList() {
    set<string> goodExtensions = {
            "bmp", "png", "tga", "jpg", "gif", "psd", "hdr", "pic"
    };

    system(command.c_str());
    fstream list;
    list.open("temp.txt");
    string line;
    vector<string> files;
    while (getline(list, line)) {
        string lineCopy = line;
        string extension;
        while (lineCopy.back() != '.') {
            extension = lineCopy.back() + extension; // NOLINT(performance-inefficient-string-concatenation)
            lineCopy.pop_back();
            if (lineCopy.empty()) {
                break;
            }
        }
        transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        if (goodExtensions.count(extension)) {
            files.push_back(line);
        }

    }
    return files;
}

int fileChoice(vector<string> list) {
    for (int i = 0; i < list.size(); i++) {
        cout << i + 1 << ": " << list[i] << endl;
    }
    int number;
    while (true) {
        cout << "Choose a file from the list: ";
        try {
            cin >> number;
            if (number < 1 || number > list.size()) {
                cout << "This is not a valid number." << endl;
                cin.clear();
                string temp;
                getline(cin, temp);
            } else {
                break;
            }
        } catch (ios_base::failure &fail) {
            cout << "This is not a valid number." << endl;
        }
    }
    return number - 1;
}

vector<string> generateSymbols(string line) {
    vector<string> symbols;
    int counts[26];
    fill(counts, counts + 26, 0);
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    string current;
    for (char i: line) {
        if (int(i) < 97 || int(i) > 122) {
            continue;
        }
        if (counts[int(i) - 97] == 0) {
            symbols.emplace_back(1, i);
        } else {
            symbols.push_back(i + to_string(counts[int(i) - 97]));
        }
        counts[int(i) - 97]++;
    }
    return symbols;
}

map<string, pair<unsigned, unsigned>> calculateWidths(unsigned imageWidth, const vector<string> &symbols) {
    double current = 0.0;
    double part = double(imageWidth) / double(symbols.size());
    map<string, pair<unsigned, unsigned>> segments;
    for (auto &symbol: symbols) {
        auto beginning = unsigned(current);
        current += part;
        auto ending = unsigned(current);
        unsigned width = ending - beginning;
        segments[symbol] = make_pair(beginning, width);
    }
    return segments;
}

bool isNumeric(char i) {
    return int(i) >= 48 && int(i) <= 57;
}

vector<string> processNewName(string line2, const map<string, pair<unsigned, unsigned>> &symbols) {
    transform(line2.begin(), line2.end(), line2.begin(), ::tolower);
    line2 += "$2$$";
    vector<string> processedSequence;
    for (int i = 0; i < line2.size(); i++) {
        string current;
        int currentChar = i;
        while (isNumeric(line2[currentChar]) || current.empty()) {
            current += line2[currentChar];
            currentChar++;
        }
        if (symbols.find(current) != symbols.end()) {
            processedSequence.push_back(current);
        }
        current.clear();
    }
    return processedSequence;
}

unsigned calculateNewImageWidth(const vector<string> &sequence, map<string, pair<unsigned, unsigned>> segments) {
    unsigned width = 0;
    for (auto &i: sequence) {
        width += segments[i].second;
    }
    return width;
}

void
createNewImage(const vector<string> &sequence, map<string, pair<unsigned int, unsigned int>> segments, Image &image,
               Image &newImage, unsigned imageHeight) {
    unsigned currentX = 0;
    for (auto &i: sequence) {
        unsigned sourceX = segments[i].first;
        unsigned sourceWidth = segments[i].second;
        newImage.copy(image, currentX, 0, IntRect(int(sourceX), 0, int(sourceWidth), int(imageHeight)));
        currentX += sourceWidth;
    }
}

int main() {
    vector<string> fileList = generateFileList();
    if (fileList.empty()) {
        cout << "There are no processable files in this directory.";
        return 0;
    }
    string chosenFile = fileList[fileChoice(fileList)];
    Image image, newImage;
    image.loadFromFile(chosenFile);
    unsigned imageWidth = image.getSize().x;
    unsigned imageHeight = image.getSize().y;
    string line1, line2;
    cout << "Name this image: ";
    getline(cin, line1);
    getline(cin, line1);
    vector<string> symbols = generateSymbols(line1);
    map<string, pair<unsigned, unsigned>> segments = calculateWidths(imageWidth, symbols);
    cout << "Generated characters: " << endl;
    for (auto &symbol: symbols) {
        cout << symbol << ' ';
    }
    cout << endl << "Write down the name of the new image using the generated characters: ";
    getline(cin, line2);
    vector<string> sequence = processNewName(line2, segments);
    cout << "New image sequence: " << endl;
    for (auto &symbol: sequence) {
        cout << symbol << ' ';
    }
    unsigned newImageWidth = calculateNewImageWidth(sequence, segments);
    newImage.create(newImageWidth, imageHeight);
    createNewImage(sequence, segments, image, newImage, imageHeight);
    for (int i = 0; i < 4; i++) {
        chosenFile.pop_back();
    }
    chosenFile += "Malep.png";
    newImage.saveToFile(chosenFile);
    cout << endl << "New image was saved to " << chosenFile << endl;
    return 0;
}


