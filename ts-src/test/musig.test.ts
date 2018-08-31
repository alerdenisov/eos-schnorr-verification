import * as eosic from "eosic";
import Eos, { IEosContract, Name, IEosjsCallsParams } from "eosjs";
import { assert } from "chai";
import "mocha";

interface IMusigContract extends IEosContract {
  exec(extra?: any): Promise<any>;
}

describe("musig", () => {
  let musigAccount: Name, musigContract: IMusigContract;

  const [pub, wif] = [
    "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV",
    "5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3"
  ];

  const eos = Eos({
    httpEndpoint: "http://0.0.0.0:8888",
    keyProvider: wif,
    expireInSeconds: 1000
  });

  beforeEach(async () => {
    ({
      account: musigAccount,
      contract: musigContract
    } = await eosic.createContract<IMusigContract>(pub, eos, "musig"));

    console.log(
      await eos.getAccount({
        account_name: musigAccount,
        json: true
      })
    );
  });

  it("exec", async () => {
    console.log(musigAccount);
    console.log(
      await musigContract.exec({
        authorization: [musigAccount]
      })
    );
  });
});
