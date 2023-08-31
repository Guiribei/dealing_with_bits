<a name="Data compression"></a>

<h2 align="center">Data Compression</h2>
  <h4 align="center">
    Algoritimo de Huffman e <i>Shared Memory Operations</i>
    <br/>
  </h4>
</div>

<details>
  <summary>Sumário</summary>
  <ol>
    <li>
      <a href="#resumo-do-projeto">Resumo do Projeto</a>
      <ul>
        </a></li>
      </ul>
    </li>
    <li>
      <a href="#fluxo-do-projeto">Fluxo do projeto</a>
      <ul>
        </a></li>
        </a></li>
      </ul>
    </li>
    <li><a href="#execução">Execução</a></li>
    <li><a href="#principais-fontes">Principais Fontes</a></li>
  </ol>
</details>



## Resumo do Projeto

O desafio da quarta edição do labs era fazer um algoritmo de compressão de Huffman que usasse operações de compartilhamento de memória para trafegar dados de um encoder para um decoder. Durante a semana de prazo para desenvolvimentos a solução criada envolveu a tradução do texto do infile.txt, codificação desse texto, compressão dele e depois descompressão e descodificação.

Principais aprendizados:
* Algoritmos de compressão
* Construção de árvore binária
* Codificação (compressão e descompressão) bit a bit
* Compartilhamento de memória entre programas
* Otimização de fluxo de código


A colaboração foi essencial nesse projeto e destaco principalmente os cadetes: ridalgo- acesar-l fnacarel etachott sguilher mameneze harndt revieira e rleite-s.




## Fluxo do Projeto

<br/>
<p align="center"> <img src="https://user-images.githubusercontent.com/85483589/212558718-cb39d641-ce04-454b-a1c5-258d91619a9c.png"> </p>
<br/>

Para compilar é necessário rodar o makefile. Dois binários são gerados, encoder e decoder. Os dois devem ser sequencialmente executados.
<br/>
<br/>
O programa ./encoder vai pegar o conteúdo do arquivo chamado "infile.txt", gerar uma tabela de frequência (que é um array de 128 posições) e jogar essa tabela para uma função que ordena de forma crescente os elementos que apareceram na string.
<br/>
<br/>
Depois disso, a lista é transformada em uma árvore binária usando uma struct com ponteiros para left e right. A árvore serve para poder gerar um dicionário que dá um código único para cada caractere que aparece no texto a ser codificado. Os caracteres de maior ocorrência recebem uma sequência de zeros e uns menor e os caracteres de menor frequência recebem um código maior.
<br/>
<p align="center"> <img src="https://user-images.githubusercontent.com/85483589/212559922-10695958-a1c0-4163-81ff-71db20908454.png"> </p>
<br/>
A árvore de Huffman foi criada para gerar uma codificação menor para os caracteres que têm mais ocorrência. Eles então ficam em níveis mais superiores da árvore, enquanto os caracteres de menor ocorrência ficam em níveis inferiores.

<br/>
<p align="center"> <img src="https://user-images.githubusercontent.com/85483589/212559485-308b3f5e-0e13-4e9d-9d6e-91f0c1bb216a.png"> </p>
<br/>

Uma outra função recebe esse código e compacta ele através da manipulação de bits, aglutinando a sequência  de zeros e uns (que é o texto codificado) a cada 8 bits em um byte para poder reduzir o tamanho. O byte que é gerado muitas vezes é um símbolo aleatório (um char entre 0 e 255). Isso é o que de fato comprime a string, fazendo com que se usem menos bytes para poder escrever a mesma quantidade de informação. É importante lembrar que um dos grandes benefícios do algoritmo de Huffman é que ele foi pensado para não perder dados no processo de compactação.

<br/>
<p align="center"> <img src="https://user-images.githubusercontent.com/85483589/212559567-b8d2fcc0-a9a8-46e3-afab-32543b72e42b.png"> </p>
<br/>

<br/>
<br/>
A string então é enviada por memória compartilhada ao programa ./decoder. O decoder lê do segmento de memória reservado para o compartilhamento tanto a string codificada quanto o dicionário. Daí ela faz a descompressão e depois uma função itera sobre a string transformando-a de volta no texto original usando o dicionário para traduzir.

### Execução

Depois de clonar o repositório, basta rodar os dois programas cada um em um terminal.
```sh
make
```
* terminal 1
  ```sh
  ./encoder
  ```
* terminal 2
    ```sh
  ./decoder
    ```

<br/>
<p align="center"> <img src="https://user-images.githubusercontent.com/85483589/212560913-ef8b9d2f-b614-4b67-8183-69667d359ecd.gif"> </p>
<br/>

## Principais fontes:

Algoritmo de Huffman: <br/>
[https://www.youtube.com/watch?v=o8UPZ_KDWdU&list=PLqJK4Oyr5WShtxF1Ch3Vq4b1Dzzb-WxbP](https://www.youtube.com/watch?v=o8UPZ_KDWdU&list=PLqJK4Oyr5WShtxF1Ch3Vq4b1Dzzb-WxbP)
<br/>
[https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/](https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/)
<br/>
[https://www.programiz.com/dsa/huffman-coding](https://www.programiz.com/dsa/huffman-coding)
<br/>
[https://www.youtube.com/watch?v=-TonlL3vcGk](https://www.youtube.com/watch?v=-TonlL3vcGk)
<br/>
<br/>
Shared Memory Operations: <br/>
[https://www.geeksforgeeks.org/ipc-shared-memory/](https://www.geeksforgeeks.org/ipc-shared-memory/)
<br/>
[https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_shared_memory.htm](https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_shared_memory.htm)
<br/>
[https://www.youtube.com/watch?v=rPV6b8BUwxM](https://www.youtube.com/watch?v=rPV6b8BUwxM)
<br/>
<br/>
Árvore Binária: <br/>
[https://www.ime.usp.br/~pf/algoritmos/aulas/bint.html](https://www.ime.usp.br/~pf/algoritmos/aulas/bint.html)
<br/>
[https://www.youtube.com/watch?v=z7XwVVYQRAA&list=PL8iN9FQ7_jt7LwqmdiyhVVu2J4jQQ9uRW&index=7](https://www.youtube.com/watch?v=z7XwVVYQRAA&list=PL8iN9FQ7_jt7LwqmdiyhVVu2J4jQQ9uRW&index=7)
<br/>
[https://www.youtube.com/watch?v=UbhlOk7vjVY](https://www.youtube.com/watch?v=UbhlOk7vjVY)

<p align="right">(<a href="#Data compression">voltar ao início</a>)</p>
