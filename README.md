<<<<<<< HEAD
# MiniHV - Escopo 25

Hipervisor monolítico desenvolvido em C11 estrito para a unidade curricular.

## Funcionalidades Implementadas
- **Arquitetura**: C11 estrito (-std=c11 -Wall -Wextra -Werror -pedantic), sem *warnings* nem fugas de memória.
- **Escalonamento**: Política LOTTERY (=5$), suporte a 1 pCPU e até 4 VMs.
- **Gestão de Memória**: Paginação PAG com algoritmo de substituição NRU e cota local.
- **Armazenamento**: Algoritmo de disco LOOK.
- **Logs e Extra**: Registo de eventos em JSONL (minihv_output.jsonl) e funcionalidade de SNAPSHOT (minihv_snapshot.jsonl).

## Como Compilar e Executar
Certifica-te de que tens o GCC instalado e corre:
`ash
make
./minihv.exe
`
=======
# MiniHV - Hipervisor Simulado (Escopo 25)

**Aluno:** Luis Fernando Duarte  
**Curso:** Engenharia de Software — UniEVANGÉLICA  
**Disciplina:** Sistemas Operacionais / Infraestrutura  

---

## 📌 Visão Geral
O **MiniHV** é um hipervisor monolítico simulado desenvolvido em **C11 estrito**, concebido para gerir a execução de Máquinas Virtuais (VMs) na arquitetura fictícia **MV-ISA**. O projeto segue uma arquitetura modular limpa e sem dependências externas.

---

## ⚙️ Especificação do Escopo 25
* **Escalonador de CPU:** `LOTTERY` (Sorteio Ponderado por Bilhetes, $q = 5$ ticks) + Política `FCFS` de referência.
* **Topologia:** 1 pCPU física | Até 4 VMs simultâneas.
* **Gestão de Memória:** Paginação por Demanda (`PAG`), Algoritmo de Substituição `NRU` (Not Recently Used) com Escopo **LOCAL** (Cota fixa de frames por VM).
* **Hardware de Memória:** 1024 palavras físicas | Páginas de 64 palavras.
* **Agendamento de Disco:** Algoritmo `LOOK` (Cilindros 0–199, Posição Inicial: 50).
* **Formato de Log:** `JSONL` (`minihv_output.jsonl`).
* **Recurso Extra:** `SNAPSHOT` (Persistência e recuperação do estado completo da VM em disco).

---

## 🛠️ Como Compilar e Executar

### Pré-requisitos
* Compilador GCC compatível com C11 (`-std=c11`).
* Utilitário `make` e `valgrind` (para análise de memória).

### Comandos Principais
```bash
# Compilar o projeto estritamente sem warnings
make

# Executar a simulação em modo batch
./minihv.exe

# Executar em modo interativo
./minihv.exe -i

# Executar os testes unitários por módulo
make test

# Verificar vazamentos de memória com Valgrind
make valgrind

# Limpar ficheiros gerados e executáveis
make clean
>>>>>>> f0dace87a8328fa0e3bdc9868011e670641b591c
