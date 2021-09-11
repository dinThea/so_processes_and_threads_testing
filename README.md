## Ambiente de testes
Todos os comandos e programas foram executados em uma máquina rodando Ubuntu 20.08, em um subsistema WSL dentro do Windows, a configuração do sistema WSL é:

```ìni
[wsl2]
memory=3GB
processors=4
```

## Respostas do Questionário:
### 1. Determinar quantos processos e quantas threads é possível criar no sistema Linux que você usa.

#### Processos:
  - Utilizando ```cat /proc/sys/kernel/pid_max``` o resultado obtido foi 32768 processos
  - Utilizando tanto ```ulimit -Sa``` (soft limit) quanto ```ulimit -Ha``` o número máximo de processos disponíveis para um único usuário é 11685.
  - Utilizando teste empírico o limite alcançado foi de 11565 processos.
  
#### Threads:
  - Utilizando ```cat /proc/sys/kernel/threads-max``` o resultado obtido foi 23370 threads
  - Utilizando o teste empírico o limite alcançado foi de 1046898 threads.

### 2. Qual foi o gargalo (**) para essa criação: identificadores? Memória? Outro fator? Como mediu?

#### Processos:
O erro foi de falta de identificadores, como pode ser observado pelo log de erro:
```
Failed to execute process '/usr/bin/id'. Reason:
exec: Resource temporarily unavailable
```   

#### Threads:
O erro foi de memória, os recursos foram acompanhados via htop e a memória chegou ao limite durante a execução, o log de erro foi:
```
terminated by signal SIGSEGV (Address boundary error)
```

### 3. Além de  verificar quantas tarefas (processos ou threads) podem ser criadas, compare o tempo para criar processos e para criar threads. 

Logs de tempo:
```
Mean thread creation time: 0.003383s
Mean process creation time: 0.006480s
```
## 4. Ao testar o programa, usar o comando ulimit no shell para reduzir o número máximo de processos permitidos e testar o programa novamente.
   Aproveitando, como será que o shell trata o comando ulimit?