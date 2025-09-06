#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

const string ClientsFileName = "Client.txt";
//vector<sClient> vClients;

struct sClient {
    string AccountNumber;
    string Pincode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

sClient ReadNewClient() {
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);
    cout << "Enter PinCode? ";
    getline(cin, Client.Pincode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;
    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.Pincode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sword;
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sword = S1.substr(0, pos);
        if (sword != "")
        {
            vString.push_back(sword);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.Pincode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}
void PrintClientRecor(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.Pincode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nName : " << Client.Name;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.Pincode;
    cout << "\nPhone : " << Client.Phone;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }

}

//[1] ShowClientList
void ShowClientList()
{
    sClient Client;
    vector<sClient>vClients;
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecor(Client);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void AddNewClient_()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
//[2] AddNewClient
void AddNewClient()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << "Adding New Client: \n\n";
        AddNewClient_();
        cout << "\nClient Added Successfully, do you want to add  more clients ? Y / N ? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');

}
//[3] DeleteClient
void DeleteClient() {
    string AccountNumber;
    cout << "Enter Account Number to Delete: ";
    cin >> AccountNumber;

    vector<sClient> clients;
    fstream MyFile(ClientsFileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            vector<string> vClientData;
            size_t pos = 0;
            string token;
            string delimiter = "#//#";
            while ((pos = Line.find(delimiter)) != string::npos) {
                token = Line.substr(0, pos);
                vClientData.push_back(token);
                Line.erase(0, pos + delimiter.length());
            }
            if (!Line.empty()) vClientData.push_back(Line);
            if (vClientData[0] != AccountNumber) {
                sClient Client;
                Client.AccountNumber = vClientData[0];
                Client.Pincode = vClientData[1];
                Client.Name = vClientData[2];
                Client.Phone = vClientData[3];
                Client.AccountBalance = stod(vClientData[4]);
                clients.push_back(Client);
            }
        }
        MyFile.close();
    }
    fstream MyFileOut(ClientsFileName, ios::out);
    if (MyFileOut.is_open()) {
        for (const auto& Client : clients) {
            MyFileOut << Client.AccountNumber << "#//#" << Client.Pincode << "#//#"
                << Client.Name << "#//#" << Client.Phone << "#//#"
                << Client.AccountBalance << endl;
        }
        MyFileOut.close();
        cout << "Client Deleted Successfully!\n";
    }
    else {
        cout << "Error opening file to write.\n";
    }
}
//[4] Update Client Info
bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.Pincode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

void UpdateClientInfo()
{
    vector <sClient> vClients;
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        
    }
}
string ReadClientAccountNumber()
{
    string AcountNumbebr = "";
    cout << "Please Enter Your AccountNumber? ";
    cin >> AcountNumbebr;

    return AcountNumbebr;
}
//[5] Find Client
vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient>vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;

}
void FindClient()
{
    sClient Client;

    string AcountNumbebr = "";
    cout << "Please Enter Your AccountNumber? ";
    cin >> AcountNumbebr;

    vector<sClient>vClients = LoadCleintsDataFromFile(ClientsFileName);
    for (sClient C : vClients)
    {
        if (C.AccountNumber == ReadClientAccountNumber())
        {
            Client = C;
        }
    }
    cout << "\nThe following are the client details:\n";
    cout << "\nName : " << Client.Name;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.Pincode;
    cout << "\nPhone : " << Client.Phone;
}

string bank()
{
    while (true) {
        cout << "\n========BY=OSAMA=REDA=============\n";
        cout << "==================================\n";
        cout << "       Main Menu Screen   \n";
        cout << "==================================\n";
        cout << "[1] Show Client List.\n";
        cout << "[2] Add New Client.\n";
        cout << "[3] Delete Client.\n";
        cout << "[4] Update Client Info.\n";
        cout << "[5] Find Client.\n";
        cout << "[6] Exit.\n";
        cout << "==================================\n";
        cout << "Choose what do you want to do? [1 to 6]? ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            ShowClientList();
            break;
        case 2:
            AddNewClient();
            break;
        case 3:
            DeleteClient();
            break;
        case 4:
            UpdateClientInfo();
            break;
        case 5:
            FindClient();
            break;
        case 6:
            cout << "Exiting the program.......!\n";
            return 0;
        default:
            cout << "Invalid choice, please choose again....\n";
            break;
        }
    }
}
int main() {
    
    bank();


    return 0;
}
