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

string removePontuacao(const std::string& palavra) {
    string pontuacoes = ".,:;!?”\"'"; 

    size_t posInicio = palavra.find_first_not_of(pontuacoes);        // Encontra a posição do primeiro caractere não pertencente à lista de pontuação

    size_t posFim = palavra.find_last_not_of(pontuacoes);            // Encontra a posição do último caractere não pertencente à lista de pontuação

    if (posInicio != string::npos && posFim != string::npos) {       // Verifica se foi encontrado algum caractere

        return palavra.substr(posInicio, posFim - posInicio + 1);
    } else {
        return "";                                                   // A palavra é composta apenas de caracteres de pontuação
    }
}


int main() {
    string estrutura;
    cin >> estrutura;

    int N;
    int i = 0;
    cin >> N;

    
    TS<string>* ts;  // Ponteiro para a classe base TS<string>

    if (estrutura == "VO") ts = new TSVO<string>();
    else if (estrutura == "ABB") ts = new TSABB<string>();
    else if (estrutura == "TR") ts = new TSTREAP<string>(N);
    else if (estrutura == "A23") ts = new A23<string>();
    else if (estrutura == "ARN") ts = new ARN<string>();


    vector<string> palavras;
    int count = 0;

    while (i < N){
        string key;
        cin >> key;
        cin.ignore();   // Descarta caracteres indesejados no buffer

        key = removePontuacao(key);
        
        size_t posicaoHifen = key.find("-"); 
        if (posicaoHifen != string::npos) {                     //Caso não tem hifen posicaoHifen gera um valor que não possui dentro do tamanho da string
            int p = 0;                          
                while (posicaoHifen != string::npos) {          // Caso que a palavra possui um ou mais hifens (ex: obrigou-se)
                    string parteSemHifen = key.substr(p, posicaoHifen);

                    auto iterador = find(palavras.begin(), palavras.end(), parteSemHifen);
                    if (iterador == palavras.end()) palavras.push_back(parteSemHifen);   // Adiciona no vetor palavras caso ja não steja lá

                    p = posicaoHifen + 1 + p;
                    posicaoHifen = key.substr(p).find("-");

                    Item infos;
                    infos.numOcorrencia = 1;
                    infos.numLetras = parteSemHifen.length();
                    infos.vogaisSR = VSR(parteSemHifen);

                    ts->add(parteSemHifen,infos);

                    i++;
                }

            // Última parte da string após o último hífen
            string parteFinal = key.substr(p);

            auto iterador = find(palavras.begin(), palavras.end(), parteFinal);
            if (iterador == palavras.end()) palavras.push_back(parteFinal);

            Item infos;
            infos.numOcorrencia = 1;
            infos.numLetras = parteFinal.length();
            infos.vogaisSR = VSR(parteFinal);
            ts->add(parteFinal,infos);

            i++;
        }
        else{
            auto iterador = find(palavras.begin(), palavras.end(), key);   //caso nao esteja no meu vetor eu adiciono ela
            if (iterador == palavras.end()){ 
                palavras.push_back(key);   
            }

            Item infos;
            infos.numOcorrencia = 1;
            infos.numLetras = key.length();
            infos.vogaisSR = VSR(key);
            
            ts->add(key,infos);

            i++;
        }
    }
    
    int Q;
    cin >> Q;
    cin.ignore();  // Descarta caracteres indesejados no buffer

    for(int k = 0; k < Q; k++){
        string consulta;
        getline(cin, consulta,'\n');

        if (consulta == "F"){
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

        else if (consulta == "L"){
            for(int j = 0; j < palavras.size(); j++){
                if(ts->value(palavras.at(j)).numLetras == ts->palavraMaisLonga){
                        cout << palavras.at(j) << " ";
                }
            }
            cout << endl;
        }

        else if (consulta == "SR"){
            if(ts->palavraNRL == -1) cout << "Todas as palavras repetem pelo menos uma letra" << endl;

            else{
                for(int j = 0; j < palavras.size(); j++){
                    if(NRL(palavras.at(j)) == ts->palavraNRL){
                        cout << palavras.at(j) << " " ;
                    }
                }
                cout << endl;
            }
        }

        else if (consulta == "VD"){
            vector<string> menores(palavras.size());  //Vetor que contém todas as palavras com mais vogais sem repetição
            int contador = 0;
            int menor = ts->palavraMaisLonga + 1;
            for(int j = 0; j < palavras.size(); j++){
                if(ts->value(palavras.at(j)).vogaisSR == ts->palavraVSR){
                    if (ts->value(palavras.at(j)).numLetras < menor) menor = ts->value(palavras.at(j)).numLetras;
                    menores.at(contador) = palavras.at(j);
                    contador++;
                }
            }
            for(int j = 0; j < contador; j++){
                if(menor == menores.at(j).length()) cout << menores.at(j) << " " << endl;
            }
        }

        else if (consulta.substr(0,2) == "O "){
            auto presente = std::find(palavras.begin(), palavras.end(), consulta.substr(2));
            if (presente != palavras.end()) {
                cout << ts->value(consulta.substr(2)).numOcorrencia << endl;
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