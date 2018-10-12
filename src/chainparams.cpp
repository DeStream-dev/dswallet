// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "base58.h"
#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

void MineGenesis(CBlock genesis){
    // This will figure out a valid hash and Nonce if you're creating a different genesis block:
    uint256 hashTarget = CBigNum().SetCompact(Params().ProofOfWorkLimit().GetCompact()).getuint256();
    printf("Target: %s\n", hashTarget.GetHex().c_str());
    uint256 newhash = genesis.GetHash();
    uint256 besthash;
    memset(&besthash,0xFF,32);
    while (newhash > hashTarget) {
    	++genesis.nNonce;
        if (genesis.nNonce == 0){
            printf("NONCE WRAPPED, incrementing time");
            ++genesis.nTime;
        }
	newhash = genesis.GetHash();
	if(newhash < besthash){
	    besthash=newhash;
	    printf("New best: %s\n", newhash.GetHex().c_str());
	}
    }
    printf("Found Genesis, Nonce: %ld, Hash: %s\n", genesis.nNonce, genesis.GetHash().GetHex().c_str());
    printf("Gensis Hash Merkle: %s\n", genesis.hashMerkleRoot.ToString().c_str());
}

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {

public:
    CMainParams() {
        initialWalletAddresses.clear();
        initialWalletAddresses.push_back("DSjHXyKyLohMfAqgCysExqd5DiFh29tqv1");
        initialWalletAddresses.push_back("DHuGPft3AdTgkYi968dxP2u8ogxCMi8BS2");
        initialWalletAddresses.push_back("DMq4LzAP1HENXQspfLdcP7kG7RBkhaxgPy");
        initialWalletAddresses.push_back("DPWqhQg2Dx9RHS19jQpU1PXdEtAfzQqwPZ");
        initialWalletAddresses.push_back("DNFXhZUmM6BrB9u47jDJvP85LbroH2T1CG");
        initialWalletAddresses.push_back("DHFj5Su8Mo2yfqYCEUKWMYL3u478CKUtxR");
        initialWalletAddresses.push_back("DBMKqJV3kJh8bhjvFd4hDAUpgLTtRxQsHu");
        initialWalletAddresses.push_back("DCeWkRsA443etVaKx3bDuJvmEp1PDnxDqt");
        initialWalletAddresses.push_back("DECLdDB4j4FUmvq6eM4bXGimRUijR5ogwa");
        initialWalletAddresses.push_back("DR9wL3g6yR6kds4WnHweL76GGfbxysuPhu");
        //const int64_t InitialCoins = 600000000000000000;
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x70;
        pchMessageStart[1] = 0x35;
        pchMessageStart[2] = 0x22;
        pchMessageStart[3] = 0x05;
        vAlertPubKey = ParseHex("0486bce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284");
        nDefaultPort = 0xDE01;
        nRPCPort = 0xDE00;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "http://www.theonion.com/article/olympics-head-priestess-slits-throat-official-rio--53466";

        hashGenesisBlock = Genesis.GetHash();

        //assert(hashGenesisBlock == uint256("0x0000066e91e46e5a264d42c89e1204963b2ee6be230b443e9159020539d972af"));
        //assert(genesis.hashMerkleRoot == uint256("0x65a26bc20b0351aebf05829daefa8f7db2f800623439f3c114257c91447f1518"));

        vSeeds.push_back(CDNSSeedData("Node1", "node1.destream.io"));
        vSeeds.push_back(CDNSSeedData("Node2", "node2.destream.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 90);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, (30+98));
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xC2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0xDD).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 12500;
    }

    virtual const std::list<string> ListInitialWalletAddresses() const { return initialWalletAddresses; }
    virtual const CBlock& GenesisBlock() const { return Genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock Genesis;
    vector<CAddress> vFixedSeeds;
    CBlock CreateDeStreamGenesisBlock(unsigned int nTime, unsigned int nNonce,
                                      unsigned int nBits, int nVersion){
        CBlock genesis;
        const char* pszTimestamp = "DESTREAM IS THE FIRST DECENTRALIZED GLOBAL FINANCIAL ECOSYSTEM FOR STREAMERS";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(initialWalletAddresses.size());
        int i = 0;
        int64_t test =InitialCoins()/ListInitialWalletAddresses().size();
        BOOST_FOREACH(string  dest, initialWalletAddresses){
            vout[i].nValue=InitialCoins()/ListInitialWalletAddresses().size();
            vout[i].scriptPubKey.SetDestination(CBitcoinAddress(dest).Get());
            i++;
        }
        CTransaction txNew(1, nTime, vin, vout, 0);
        genesis.hashPrevBlock = 0;
        genesis.nTime = nTime;
        genesis.vtx.push_back(txNew);
        genesis.nBits  = nBits;
        genesis.nNonce = nNonce;
        genesis.nVersion = nVersion;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        hashGenesisBlock = genesis.GetHash();
        return genesis;

    }
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        initialWalletAddresses.clear();
        initialWalletAddresses.push_back("DSjHXyKyLohMfAqgCysExqd5DiFh29tqv1");
        initialWalletAddresses.push_back("DHuGPft3AdTgkYi968dxP2u8ogxCMi8BS2");
        initialWalletAddresses.push_back("DMq4LzAP1HENXQspfLdcP7kG7RBkhaxgPy");
        initialWalletAddresses.push_back("DPWqhQg2Dx9RHS19jQpU1PXdEtAfzQqwPZ");
        initialWalletAddresses.push_back("DNFXhZUmM6BrB9u47jDJvP85LbroH2T1CG");
        initialWalletAddresses.push_back("DHFj5Su8Mo2yfqYCEUKWMYL3u478CKUtxR");
        initialWalletAddresses.push_back("DBMKqJV3kJh8bhjvFd4hDAUpgLTtRxQsHu");
        initialWalletAddresses.push_back("DCeWkRsA443etVaKx3bDuJvmEp1PDnxDqt");
        initialWalletAddresses.push_back("DECLdDB4j4FUmvq6eM4bXGimRUijR5ogwa");
        initialWalletAddresses.push_back("DR9wL3g6yR6kds4WnHweL76GGfbxysuPhu");
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x71;
        pchMessageStart[1] = 0x31;
        pchMessageStart[2] = 0x21;
        pchMessageStart[3] = 0x11;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 0xDE11;
        nRPCPort = 0xDE10;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 90);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, (30+98));
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        strDataDir = "testnet";
        unsigned int nTime = 1539353822;
        unsigned int nNonce = 2433759;
        unsigned int nBits = 520159231;
        int nVersion = 1;
        Genesis = CreateDeStreamGenesisBlock(nTime, nNonce, nBits, nVersion);
        //assert(hashGenesisBlock == uint256("0xac5e9afbc85e67ea5edf0116b96910526d75662ee833a70163cb3b4a6d2423e8"));
        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("Testnode1", "testnode1.destream.io"));
        vSeeds.push_back(CDNSSeedData("Testnode2", "40.121.9.206"));
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        nLastPOWBlock = 0x7fffffff;
    }

    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        Genesis.nTime = 1411111111;
        Genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        Genesis.nNonce = 1659424;
        hashGenesisBlock = Genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
//        MineGenesis(genesis);
        //assert(hashGenesisBlock == uint256("0x00000d97ffc6d5e27e78954c5bf9022b081177756488f44780b4f3c2210b1645"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

//static CChainParams *pCurrentParams = &mainParams;
static CChainParams *pCurrentParams = &testNetParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
