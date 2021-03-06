"use strict";
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];
    result["default"] = mod;
    return result;
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const eosic = __importStar(require("eosic"));
const eosjs_1 = __importDefault(require("eosjs"));
require("mocha");
describe("musig", () => {
    let musigAccount, musigContract;
    const [pub, wif] = [
        "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV",
        "5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3"
    ];
    const eos = eosjs_1.default({
        httpEndpoint: "http://0.0.0.0:8888",
        keyProvider: wif,
        expireInSeconds: 1000
    });
    beforeEach(async () => {
        ({
            account: musigAccount,
            contract: musigContract
        } = await eosic.createContract(pub, eos, "musig"));
        console.log(await eos.getAccount({
            account_name: musigAccount,
            json: true
        }));
    });
    it("exec", async () => {
        console.log(musigAccount);
        console.log(await musigContract.exec({
            authorization: [musigAccount]
        }));
    });
});
