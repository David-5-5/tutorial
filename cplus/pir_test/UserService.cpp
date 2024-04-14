#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef long raw_data;
int NX = 200;

int PAYLOAD_LENGTH;

raw_data *data_sender;
unordered_map<raw_data, string> *payload;

void encoder_int(int a, vector<unsigned char> &concat) {
    for (int i = 0; i < sizeof(int); i++) {
        concat.push_back((a >> (i * 8)) & 0xFF);
    }
}

void encoder_char(unsigned char a, vector<unsigned char> &concat) {
    for (int i = 0; i < sizeof(unsigned char); i++) {
        concat.push_back((a >> (i * 8)) & 0xFF);
    }
}

void data_loader_service(string path)
{
    ifstream fp(path);
    string payload_tmp;

    for (long i = 0; i < NX; i++)
    {
        string id;
        string date;
        int age;
        double spend;
        int date_int;
        int spend_int;

        getline(fp, payload_tmp, '\n');
        // cout << payload_tmp << endl;
        istringstream iss(payload_tmp);
        if (iss >> id >> date >> age >> spend)
        {
            size_t pos = date.find("-");
            while ((pos != string::npos))
            {
                date.replace(pos, 1, "");
                pos = date.find("-", pos + 0);
            }
            date_int = atoi(date.c_str());
            spend_int = (int)(spend * 100);
        }
        vector<unsigned char> concat;

        // encoder
        encoder_int(date_int, concat);
        encoder_char((unsigned char)age, concat);
        encoder_int(spend_int, concat);

        unsigned char bytes[concat.size()];
        for (int i = 0; i < concat.size(); i++)
        {
            bytes[i] = concat[i];
        }
        string value(reinterpret_cast<char *>(bytes), concat.size());

        data_sender[i] = atol(id.c_str());

        // cout << "id: " << data_sender[i] << " value: " << value << endl;
        if (value.length() < PAYLOAD_LENGTH)
        {
            value.append(PAYLOAD_LENGTH - value.length(), ' ');
        }
        else if (value.length() > PAYLOAD_LENGTH)
        {
            cout << "error!!!: " << value << endl;
            for (int j = 0; j < value.length(); j++)
            {
                printf("%d\n", value[j]);
            }
        }

        (*payload)[data_sender[i]] = value;
    }
}


int main(){
    data_loader_service("pir_300.txt");
}