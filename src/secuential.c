#include "shared.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void dfs(WSP *wsp, Route *route) {
  // If route completed, check if best
  if (routeCompleted(wsp, route)) {
    if (!wsp->route || route->cost < wsp->route->cost) {
      wsp->route = route;
    } else {
      routeFree(route);
    }
    printf("Finished route\n");
    return;
  }

  if (wsp->route) {
    printf("Min cost %i route %i\n", wsp->route->cost, route->cost);
  } else {
    printf("Route cost %i size %i\n", route->cost, route->size);
  }

  printf("Tour origin %i\n", route->visited[route->size - 1]->number);
  for (int d = 0; d < wsp->size - route->size; d++) {
    printf("Tour destination %i city %i\n", d, route->tour[d]->number);
  }

  // If worse than best, stop travelling
  if (wsp->route && route->cost >= wsp->route->cost) {
    routeFree(route);
    return;
  }

  // Lets keep travelling
  int destinations = wsp->size - route->size;
  // if (destinations == 1) {
  //   routeVisitDestination(wsp, route, 0);
  //   dfs(wsp, route);
  //   return;
  // }

  for (int destination = 0; destination < destinations; destination++) {
    Route *route_visit = routeInit(wsp, route);
    printf("destinations %i destination %i size %i cost %i\n", destinations,
           destination, route->size, route->cost);
    routeVisitDestination(wsp, route_visit, destination);
    dfs(wsp, route_visit);
  }
};

int main(int argc, char *argv[]) {
  /* The program receives 1 param */
  if (argc != 2) {
    printf("Modo de uso: %s <input.txt>\n", argv[0]);
    printf("\t<input.txt> es el problema a resolver\n");
    return 1;
  }
  char *input = argv[1];
  WSP *wsp = wspInit(input);
  wspPrint(wsp);

  Route *route = routeInit(wsp, NULL);
  dfs(wsp, route);
  printf("Cheapest %i\n", wsp->route->cost);

  wspFree(wsp);
  return 0;
}
