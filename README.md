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
