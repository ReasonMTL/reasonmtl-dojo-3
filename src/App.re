module Style = {
  open Css;

  let title = style([textAlign(center), color(hex("666"))]);
};

module PokemonQuery = [%graphql
  {|
    query {
      pokemons(offset: 0) {
        name
        sprites {
          default {
            front
            back
          }
        }
      }
    }
  |}
];

module GetPokemonQuery = ReasonApollo.CreateQuery(PokemonQuery);

[@react.component]
let make = () => {
  // let pokemonQuery = PokemonQuery.make();
  <div className="vh-100 vw-100 flex flex-column justify-start items-center">
    <h1 className=Style.title> {React.string({j|My Pokédex|j})} </h1>
    <GetPokemonQuery>
      ...{({result}) =>
        switch (result) {
        | Loading => <div> {React.string("Loading")} </div>
        | Error(error) => <div> {React.string(error##message)} </div>
        | Data(response) =>
          Js.log(response);

          <div className="flex flex-column">
            {React.array(
               Belt.Array.map(response##pokemons, pokemon =>
                 <span> {React.string(pokemon##name)} </span>
               ),
             )}
          </div>;
        }
      }
    </GetPokemonQuery>
  </div>;
};