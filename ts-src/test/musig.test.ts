import * as eosic from "eosic";
import Eos, { IEosContract, Name, IEosjsCallsParams } from "eosjs";
import { assert } from "chai";
import "mocha";

interface IMusigContract extends IEosContract {
  exec(extra?: IEosjsCallsParams): Promise<any>;
}

describe("priceoraclize", () => {
  let musigAccount: Name, musigContract: IMusigContract;

  const [pub, wif] = [
    "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV",
    "5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3"
  ];

  const eos = Eos({
    httpEndpoint: "http://0.0.0.0:8888",
    keyProvider: wif
  });

  beforeEach(async () => {
    ({
      account: musigAccount,
      contract: musigContract
    } = await eosic.createContract<IMusigContract>(pub, eos, "musig"));

    const charMap = ["a", "b", "c", "d", "e", "f", "g", "h", "k", "l", "m"];
    const pid = Array(5)
      .fill(0)
      .map(() => charMap[Math.floor(Math.random() * charMap.length)])
      .join("");
  });

  it("exec", async () => {
    await musigContract.exec({
      authorization: [musigAccount]
    });
  });
});
