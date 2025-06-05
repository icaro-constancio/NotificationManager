#include <iostream>        
#include <cstdlib> 
#include <curl/curl.h> 

using namespace std;

bool NotificarDiscord(const string& mensagem) {
    const char* webhook = getenv("DISCORD_WEBHOOK");
    if (!webhook) {
        cerr << "Link do webhook não encontrado\n";
        return false;
    }

    CURL* curl = curl_easy_init();
    if (!curl) return false;

    string DiscordMensagem = "{\"content\": \"" + mensagem + "\"}";
    struct curl_slist* headers = curl_slist_append(nullptr, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, webhook);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, DiscordMensagem.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode resultado = curl_easy_perform(curl);
    bool sucesso = (resultado == CURLE_OK);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return sucesso;
}

bool NotificarEmail() {
    const char* emailUsuario = getenv("EMAIL_USUARIO"); 
    const char* emailSenha = getenv("EMAIL_SENHA");
    const char* emailDestinatario = getenv("EMAIL_DESTINATARIO");

    if (!emailUsuario || !emailSenha || !emailDestinatario) {
        cerr << "Variavéis de Ambiente não encontradas\n" ;
        return false;
    }

    CURL* curl = curl_easy_init();
    if (!curl) return false;

    //Configurações básicas
    curl_easy_setopt(curl, CURLOPT_USERNAME, emailUsuario);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, emailSenha);
    curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");

    //Define o remetente e o destinatário
    string remetente = "<" + string(emailUsuario) + ">";
    string destinatario = "<" + string(emailDestinatario) + ">";
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, remetente.c_str());
    struct curl_slist* listaDestinatarios = curl_slist_append(nullptr, destinatario.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, listaDestinatarios);

    //Cria o corpo do e-mail
    string corpo = "testando.";
    string assunto = "Subject: Email de Teste";
    struct curl_slist* headers = curl_slist_append(nullptr, assunto.c_str());

    curl_mime* mime = curl_mime_init(curl);
    curl_mimepart* parte = curl_mime_addpart(mime);
    curl_mime_data(parte, corpo.c_str(), CURL_ZERO_TERMINATED);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode resultado = curl_easy_perform(curl);
    bool sucesso = (resultado == CURLE_OK);

    //Libera memória
    curl_slist_free_all(listaDestinatarios);
    curl_slist_free_all(headers);
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    return sucesso;
}

int main() {
    char opcao;
    cout << "Tecla d - Notificar Discord\n";
    cout << "Tecla e - Notificar E-mail\n";
    cout << "Tecla 0 - Encerrar\n";

    do {
        cout << "\nPressione uma tecla : ";
        cin >> opcao;

        switch (tolower(opcao)) {
            case 'd':
                if (NotificarDiscord(""))
                    cout << "Notificação Enviada\n";
                else
                    cout << "Notificação não enviada\n";
                break;

            case 'e':
                if (NotificarEmail())
                    cout << "E-mail Enviado\n";
                else
                    cout << "E-mail não enviado\n";
                break;

            case '0':
                cout << "Encerrado\n";
                break;

            default:
                cout << "A opção não existe, escolha outra\n";
        }

    } while(opcao != '0');

    return 0;
}