module Style = {
  open Css;

  let title = style([textAlign(center), color(hex("666"))]);
  let pokelist = style([
    display(flexBox),
    flexWrap(wrap),
    width(pct(100.0)),
    ]);

  let pokemon = style([
    height(px(300)),
    width(px(300)),
    backgroundColor(rgba(50, 20, 100, 1.0)),
    margin(px(20)),
    padding(px(20)),
    color(white),
  ]);

  let pokemonImg = style([width(px(200))])
};

module PokemonQuery = [%graphql
  {|
    query {
      pokemons(offset: 0) {
        id
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

          <div className=Style.pokelist>
            {React.array(
               Belt.Array.map(response##pokemons, pokemon =>
                 <div className=Style.pokemon key={string_of_int(pokemon##id)}> 
                  {React.string(pokemon##name)} 
                  <img src={pokemon##sprites##default##front} className=Style.pokemonImg />
                  </div>
               ),
             )}
          </div>;
        }
      }
    </GetPokemonQuery>
  </div>;
};