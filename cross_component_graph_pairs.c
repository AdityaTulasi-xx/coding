#include <stdio.h>

typedef struct _edge
{
    int dest;
    int next_idx;
} edge;

int cur_component;
int cur_component_size;
int cur_edge_count = 0;
edge graph_edges[20002];
int neighbor_lists[100001];
int component_sizes[100001];

int visited[100001];

void dfs_and_count(int src)
{
    if (visited[src] != 0)
    {
        return;
    }

    visited[src] = cur_component;
    cur_component_size++;
    int i = neighbor_lists[src];

    while (i != -1)
    {
        if (visited[graph_edges[i].dest] == 0)
        {
            dfs_and_count(graph_edges[i].dest);
        }
        i = graph_edges[i].next_idx;
    }
}

int main()
{
    int node_count, edge_count;

    scanf("%d %d", &node_count, &edge_count);

    int i, j;
    int node1, node2;

    for (i = 0; i < node_count; i++)
    {
        neighbor_lists[i] = -1;
    }

    for (i = 0; i <= edge_count; i++)
    {
        scanf("%d %d", &node1, &node2);

        // adding edges both ways
        j = neighbor_lists[node1];
        graph_edges[cur_edge_count].dest = node2;
        graph_edges[cur_edge_count].next_idx = j;
        neighbor_lists[node1] = cur_edge_count;
        cur_edge_count++;

        j = neighbor_lists[node2];
        graph_edges[cur_edge_count].dest = node1;
        graph_edges[cur_edge_count].next_idx = j;
        neighbor_lists[node2] = cur_edge_count;
        cur_edge_count++;
    }

    for (i = 0; i < node_count; i++)
    {
        if (visited[i] == 0)
        {
            cur_component++;
            cur_component_size = 0;
            dfs_and_count(i);
            component_sizes[cur_component - 1] = cur_component_size;
        }
    }

    long long int ans = 0;

    for (i = 0; i < cur_component; i++)
    {
        node_count -= component_sizes[i];
        ans += ((long long)component_sizes[i] * (long long)node_count);
    }

    printf("%lld\n", ans);

    return 0;
}