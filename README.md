# NotificationManager para o Discord e Email
O meu projeto em C++ permite o envio de mensagens para um canal do **Discord via Webhook** e o envio de **e-mails via SMTP** a partir de um menu no terminal. Optei por usar variavéis de ambiente para a leitura das credenciais(remetente,destinatario,senha de aplicativo e webhook).


Requisitos
- Compilador c++
- Libcurl
- Visual Studio

### 1. Instalação da `libcurl`:

```
sudo apt install libcurl4-openssl-dev
```
## 2. Configuração das variáveis de ambiente:
Para configurar optei por adicionar as linhas abaixo no ficheiro `profile`. Isso permitiu que as credenciais fossem carregadas automaticamente toda vez que eu usasse meu programa, sem precisar configurar novamente.

**Importante: é necessário o uso de uma senha de aplicativo (não a senha pessoal da conta) para conexões SMTP
Eu gerei a minha senha em: https://myaccount.google.com/apppasswords**

Para abrir o ficheiro, digitei no terminal: 

```
code ~/.profile
```

Depois escrevi no final:

```
export EMAIL_USUARIO="substituir"
export EMAIL_SENHA=""
export EMAIL_DESTINATARIO=""
export DISCORD_WEBHOOK=""
```

No terminal novamente, para salvar tudo:
```
source ~/.profile
```

## 3. Compilação do código 
Usei o g++ no meu computador como compilador,caso não instalado no computador:

```
sudo apt install build-essential
```
Para compilar o programa:

```
g++ -o notify notificador.cpp -lcurl

```

Para rodar: 

```
./notify

```
