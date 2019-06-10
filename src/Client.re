let serverUri = "https://reasonable-pokedex-git-cors.davidcorticchiato.now.sh/graphql";

let instance =
  ReasonApollo.createApolloClient(
    ~link=ApolloLinks.createHttpLink(~uri=serverUri, ()),
    ~cache=ApolloInMemoryCache.createInMemoryCache(),
    (),
  );