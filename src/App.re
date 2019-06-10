module Style = {
  open Css;

  let title = style([textAlign(center), color(hex("666"))]);
};

[@react.component]
let make = () => {
  <> <h1 className=Style.title> {React.string({j|My Pokédex|j})} </h1> </>;
};