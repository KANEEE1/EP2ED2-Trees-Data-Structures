#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "TSVO.h"
#include "TSABB.h"
#include "TSA23.h"
#include "TSARN.h"
#include "TSTREAP.h"
#include "TS.h"

using namespace std;

int main() {
    string estrutura;
    cin >> estrutura;

    TS<string>* ts;  // Ponteiro para a classe base TS<string>

    if (estrutura == "VO") ts = new TSVO<string>();
    else if (estrutura == "ABB") ts = new TSABB<string>();
    else if (estrutura == "TR")  ts = new TSTREAP<string>();
    else if (estrutura == "A23") ts = new A23<string>();
    else if (estrutura == "ARN") ts = new ARN<string>();


    int N;
    int i = 0;
    cin >> N;
    vector<string> palavras;
    string pontuacoes = ",.;:-?!";


    while (i < N){
        string key;
        cin >> key;

        int x = 0;
        while(pontuacoes.find(key[key.length() - (++x)]) != string::npos){
            key.pop_back();
        }

        size_t hyphenPos = key.find("-");                    // Caso que a palavra possui um hifen (ex: obrigou-se)
        if (hyphenPos != string::npos) {                   
            string firstPart = key.substr(0, hyphenPos);
            auto iterador = find(palavras.begin(), palavras.end(), firstPart);
            if (iterador == palavras.end()) palavras.push_back(firstPart);
            //cout << firstPart << endl;   

            int numOcorrencia = 1;         
            int numLetras = firstPart.length();
            int vogaisSR = VSR(firstPart);

            Item infos;
            infos.numOcorrencia = numOcorrencia;
            infos.numLetras = numLetras;
            infos.vogaisSR = vogaisSR;
            ts->add(firstPart,infos);


            string secondPart = key.substr(hyphenPos + 1);
            iterador = find(palavras.begin(), palavras.end(), secondPart);
            if (iterador == palavras.end()) palavras.push_back(secondPart);   
            //cout << secondPart << endl;   

            Item infos2;
            infos2.numOcorrencia = numOcorrencia;
            infos2.numLetras = secondPart.length();
            infos2.vogaisSR = VSR(secondPart);
            ts->add(secondPart,infos2);

            i+=2;
        }

        else{
            auto iterador = find(palavras.begin(), palavras.end(), key);   //caso nao esteja no meu vetor eu adiciono ela
            if (iterador == palavras.end()){ 
                palavras.push_back(key);   
                //cout << key << endl;
            }

            int numOcorrencia = 1;         //supoe que eh a primeira vez que esta colocando
            int numLetras = key.length();
            int vogaisSR = VSR(key);

            Item infos;
            infos.numOcorrencia = numOcorrencia;
            infos.numLetras = numLetras;
            infos.vogaisSR = vogaisSR;

            ts->add(key,infos);

            i++;
        }
        //cout << i << endl;
    }
    
    int Q;
    cin >> Q;
    cin.ignore();

    for(int k = 0; k < Q; k++){
        string comando;
        getline(cin, comando,'\n');

        if (comando == "F"){
            //cout << "djadia" << ts->palavraMaisFreq << endl;
            if(ts->palavraMaisFreq == 1){
                cout << "Todas as palavras só aparecem uma vez" << endl;
            }

            else{
                for(int j = 0; j < palavras.size(); j++){
                    if(ts->value(palavras.at(j)).numOcorrencia == ts->palavraMaisFreq){
                     cout << palavras.at(j) << " ";
                    }
                }
                cout << endl;
            }
        }

        else if (comando == "L"){
            for(int j = 0; j < N; j++){
                if(ts->value(palavras.at(j)).numLetras == ts->palavraMaisLonga){
                        cout << palavras.at(j) << " ";
                        cout << endl;
                }
            }
        }

        else if (comando == "SR"){
            //cout << "entrei" << endl;
            if(ts->palavraVSR == -1) cout << "Todas as palavras repetem pelo menos uma letra" << endl;

            else{
                for(int j = 0; j < palavras.size(); j++){
                    if(NRL(palavras.at(j)) == ts->palavraNRL){
                        cout << palavras.at(j) << " " ;
                        cout << endl;
                    }
                }
            }
        }

        else if (comando == "VD"){
            vector<string> menores(palavras.size());  //Vetor que contém todas as palavras com mais vogais sem repetição
            int contador = 0;
            int menor = ts->palavraMaisLonga + 1;
            for(int j = 0; j < palavras.size(); j++){
                //cout << j << endl;
                if(VSR(palavras.at(j)) == ts->palavraVSR){
                    if (ts->value(palavras.at(j)).numLetras < menor) menor = ts->value(palavras.at(j)).numLetras;
                    menores.at(contador) = palavras.at(j);
                    contador++;
                }
            }
            for(int j = 0; j < contador; j++){
                if(menor = menores.at(j).length()) cout << menores.at(j) << " " << endl;
            }
        }

        else if (comando.substr(0,2) == "O "){
            auto presente = std::find(palavras.begin(), palavras.end(), comando.substr(2));
            if (presente != palavras.end()) {
                cout << ts->value(comando.substr(2)).numOcorrencia << endl;
            }
            else{
                cout << "Essa palavra não aparece no texto" << endl;
            }
        }

        else{
            cout << "Comando inválido" << endl;
        }
    }
    return 0;
}