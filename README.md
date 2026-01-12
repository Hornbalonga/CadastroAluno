# 📚 TI CURSOS - Sistema de Gestão de Matrículas

Sistema de gerenciamento acadêmico desenvolvido em **C** para controle de alunos, cursos e mensalidades. O projeto utiliza manipulação de arquivos binários para garantir que os dados permaneçam salvos mesmo após fechar o programa.

## 🚀 Funcionalidades

* **Cadastro de Alunos:** Registro de matrícula, nome, sexo e idade.
* **Matrícula Dupla:** Permite que um aluno se inscreva em até dois cursos diferentes.
* **Cálculo de Descontos Automático:**
    * **30% de desconto** no valor total para alunos em 2 cursos.
    * **15% de desconto** para alunos com 45 anos ou mais.
* **Edição e Exclusão:** Interface para alterar dados existentes ou remover registros do sistema.
* **Relatórios Filtrados:** Listagem geral ou filtros específicos por sexo e por curso.
* **Persistência de Dados:** Armazenamento em arquivo físico (`arquivo_alunos_matriculados.txt`).

## 🛠️ Tecnologias e Conceitos Utilizados

* **Linguagem C:** Uso de estruturas (`struct`) e tipos de dados customizados.
* **Manipulação de Arquivos (CRUD):** Uso de `fopen`, `fwrite`, `fread`, `fseek` e `rewind` para gerenciar a base de dados.
* **Localidade:** Configurado para aceitar acentuação e caracteres da língua portuguesa.

## 📋 Tabela de Cursos e Valores

| Curso | Turno | Valor (Base) |
| :--- | :--- | :--- |
| PHP | Manhã / Noite | R$ 210,00 / R$ 260,00 |
| Java | Manhã / Noite | R$ 320,00 / R$ 390,00 |
| Python | Manhã / Noite | R$ 290,00 / R$ 310,00 |

> [!NOTE]
> Valores baseados na configuração inicial do sistema.

## ⚙️ Como Executar

1. Certifique-se de ter um compilador C instalado (GCC, MinGW, etc).
2. Salve o arquivo como `main.c`.
3. Compile o programa:
   ```bash
   gcc main.c -o sistema_gestao
