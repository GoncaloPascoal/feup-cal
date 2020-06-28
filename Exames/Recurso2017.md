## Exame 2017 - Recurso

**1. a)** O algoritmo ganancioso seguinte utiliza um índice que começa no início da sequência. Enquanto o índice não chegar ao fim da sequência, procura na cadeia a primeira ocorrência de um valor igual ao apontado pelo índice. Se isto acontecer, o índice avança para o elemento depois do encontrado. Senão, o índice é simplesmente incrementado. A complexidade temporal do algoritmo no pior caso é `O(n^2)`, se os elementos da sequência forem todos diferentes.
```cpp
int greedy(const vector<int>& seq) {
    int result = 0;
    int idx = 0;

    while (idx < seq.size()) {
        ++result;

        for (int i = idx + 1; i < seq.size(); ++i) {
            if (seq[i] == seq[idx]) {
                idx = i;
                break;
            }
        }
        ++idx;
    }

    return result;
}
```
**b)**
```cpp
int dynamic(const vector<int>& seq) {

}
```

**2. a)** O algoritmo de Prim escolhe para a próxima aresta da árvore de expansão mínima aquela que tiver peso mínimo e ligar um vértice que pertence à árvore a outro que não pertence. Logo a sequência de arestas escolhidas será:
```
AB, BC, CF, FH, HG, GD, GE
```
**b)** A aresta terá de ter um peso inferior a 10, visto que a aresta escolhida depois do vértice C ser adicionado à árvore é a aresta CF, de peso 10. A outra possiblidade seria escolher esta aresta em vez de GE mas visto que o peso de GE é 5 não precisamos de considerar este caso (sempre que o peso de CE fosse inferior a 5, seria escolhida em vez de CF).

**3. a)** Tabela das distâncias e caminhos em cada passo de Dijkstra
Vértice Explorado|dA|dB|dC|dD|dE|dF|dG|dH|pA|pB|pC|pD|pE|pF|pG|pH
-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
nenhum|0|inf|inf|inf|inf|inf|inf|inf|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL
A|0|12|16|14|inf|inf|inf|inf|NULL|A|A|A|NULL|NULL|NULL|NULL
B|0|12|16|14|inf|31|inf|25|NULL|A|A|A|NULL|B|NULL|B
D|0|12|16|14|25|31|17|25|NULL|A|A|A|D|B|D|B
C|0|12|16|14|25|26|17|25|NULL|A|A|A|D|C|D|B
G|0|12|16|14|22|26|17|18|NULL|A|A|A|G|C|D|G
H|0|12|16|14|22|24|17|18|NULL|A|A|A|G|H|D|G
E|0|12|16|14|22|24|17|18|NULL|A|A|A|G|H|D|G
F|0|12|16|14|22|24|17|18|NULL|A|A|A|G|H|D|G

O caminho mais curto de A a H é `A -> D -> G -> H`

**b)** Este problema é equivalente ao problema do caminho mais curto, ignorando o peso das arestas, ou seja, ao problema do caminho mais curto para um grafo não pesado. Um algoritmo que podemos utilizar neste caso é o algoritmo da pesquisa em largura (breadth-first search):
```
bfs(G = (V, E), s):
    for v in V:
        dist(v) = infinite
        path(v) = NULL
    
    dist(s) = 0

    Q = empty_queue()
    enqueue(Q, s)

    while not Q.empty():
        v = dequeue(Q)
        for w in adj(v):
            if dist(w) == infinite:
                enqueue(Q, w)
                dist(w) = dist(v) + 1
                path(w) = v
```
Este algoritmo tem complexidade temporal `O(|E| + |V|)` onde `|E|` é o número de arestas e `|V|` o número de vértices do grafo. Este valor pode ser facilmente deduzido analisando o algoritmo: todos os vértices são explorados e cada vez que um vértice é explorado, analisamos todas as arestas que originam nesse vértice.

❓ **4. a)** O fluxo máximo a alimentar o sistema é de 10 litros / hora (tot = 7 + 3 = 10).
![](Imagens\FluxoAspersores1.png)
❓ **b)** O fluxo que passa pela tubulação `E -> H`, se for instalado um aspersor no vértice E é 0 (usando o algoritmo de Edmonds-Karp para o fluxo máximo):
![](Imagens\FluxoAspersores2.png)

**5. a)** Este problema é uma instância do problema da distância de edição entre duas strings. Neste caso a distância evolutiva entre os dois genes é 3. As mutações necessárias para converter XPTO em OPTX são:
* Inserir um `A` depois do primeiro caracter
* Remover ambos os caracteres `T` (duas mutações)

**b)**
q|pi|PRE
-|-|-
1|0|G
2|0|GT
3|1|GTG (G)
4|0|GTGC
5|0|GTGCC

**6. a)** Dado um grafo G = (V, E) e um inteiro k existe um subconjunto Vc de V de tamanho maior ou igual a k tal que para qualquer u, v pertencentes a Vc, (u, v) pertence a E?  
**b)** Um clique candidato pode ser facilmente verificado em tempo polinomial (basta percorrer todos os pares de vértices do subconjunto e verificar se existe uma aresta que os une no grafo). Logo o problema é NP. O problema do conjunto independente sugerido no enunciado é NP-completo e podemos reduzir este problema ao problema do clique em tempo polinomial:

* Fazer o complemento do grafo dado (cada par de vértices sem aresta passa a ter uma aresta que os liga e cada par de vértices que tinha uma aresta deixa de a ter). Exemplo:

![](Imagens\GrafoComplemento.png)

* Uma solução para o problema do conjunto independente no grafo complemento será solução para o problema do clique no grafo original (visto que se não existir um par de vértices do subconjunto que partilhe uma aresta no grafo complemento, todos os pares de vértices partilharão uma aresta no grafo original)

Logo podemos concluir que o problema do clique é NP-completo.