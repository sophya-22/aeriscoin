// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2014-2017 The Aeris Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

#include "stdio.h"
#include "pow.h"

static CBlock
CreateGenesisBlock(const char *pszTimestamp, const CScript &genesisOutputScript, uint32_t nTime, uint32_t nNonce,
                   uint32_t nBits, int32_t nVersion, const CAmount &genesisReward) {
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4)
                             << std::vector<unsigned char>((const unsigned char *) pszTimestamp,
                                     (const unsigned char *) pszTimestamp +
                                     strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);

    return genesis;
}


static CBlock
CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount &genesisReward) {
    const char *pszTimestamp = "New York Times 31/01/2018 President issues appeal for unity in state of union";
    const CScript genesisOutputScript = CScript() << ParseHex(
                                            "042ca677fc77f936ac22a4bc7084ec941afc15eeb8a1af3dcf6fedc09b0a8462870c08c0a9c7112516f6393fc5b08d6527a2a6f80a87d1d2373c9c5ad5512515f7")
                                        << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";

        consensus.nSubsidyHalvingInterval = 262800;
        consensus.nMasternodePaymentsStartBlock = 322;
        consensus.nMasternodePaymentsIncreaseBlock = -1;
        consensus.nMasternodePaymentsIncreasePeriod = -1;
        consensus.nInstantSendKeepLock = 94;
        consensus.nBudgetPaymentsStartBlock = 65123;
        consensus.nBudgetPaymentsCycleBlocks = 64800;
        consensus.nBudgetPaymentsWindowBlocks = 390;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 2100000000; // year 10000+
        consensus.nSuperblockCycle = 64800;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 20;

        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;

        consensus.nMajorityWindow = 3900;
        consensus.BIP34Height = -1;
        consensus.BIP34Hash = uint256S("0x000000000000024b89b42a942fe0d9fea3bb44ab7bd1b19115dd6a759c0808b8");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 30 * 2 * 60; // 1 hour, 30 blocks
        consensus.nPowTargetSpacing = 2 * 60; // 2 min
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916;
        consensus.nMinerConfirmationWindow = 2016;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1486252800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517788800;

        pchMessageStart[0] = 0x4c;
        pchMessageStart[1] = 0x61;
        pchMessageStart[2] = 0xc5;
        pchMessageStart[3] = 0x11;

        vAlertPubKey = ParseHex("041e203913367e77bf815454639a688aeb44802f5b58f8657b34f6349a90410457f1b244a3c208db8d5cd2a12007aab5c40b593f2cfd3c25b4e03dcb8516d2b8c6");
        nDefaultPort = 23100;
        nMaxTipAge = 11520;
        nPruneAfterHeight = 100000;


        genesis = CreateGenesisBlock(1517849983, 2442161, 0x1e0ffff0, 1, 50 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock ==
               uint256S("0x00000ac3b982c0b616ae1a4188c1222c340979d3c69bdeffcd757c40037ef607"));
        assert(genesis.hashMerkleRoot ==
               uint256S("0x1799a2ff8e3776c2386f8b9b554da902a79e86072f48c8bf5c702f3c29c295e4"));

        //vSeeds.push_back(CDNSSeedData("nodes.aerisx.io", "nodes.aerisx.io"));
        //vSeeds.push_back(CDNSSeedData("nodes.Aeris.org", "nodes.Aeris.org"));
        //vSeeds.push_back(CDNSSeedData("nodes.myaeriscoin.com", "nodes.myaeriscoin.com"));
        //vSeeds.push_back(CDNSSeedData("nodes.cryptophi.com", "nodes.cryptophi.com"));
        vSeeds.clear();

        // Aeris addresses start with 'A'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);
        // Aeris script addresses start with 'S'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 63);
        // Aeris private keys start with 'y' or 'z'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 79);

        // Aeris BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Aeris BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Aeris BIP44 coin type is '5' <== Should be migrated to 31 SLIP-44 Aeris
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 3600;
        strSporkPubKey = "046dac102bd50159b19640d07f8fa3618b1531a10d8bada1ec00361e5f0a2c9805d927a0c82d408db6f589683d4291fadeef20ab59b255279ff99fe88b78ee5c71";
        strMasternodePaymentsPubKey = "046dac102bd50159b19640d07f8fa3618b1531a10d8bada1ec00361e5f0a2c9805d927a0c82d408db6f589683d4291fadeef20ab59b255279ff99fe88b78ee5c71";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x00000ac3b982c0b616ae1a4188c1222c340979d3c69bdeffcd757c40037ef607"))
             ,
            1517849983,
            0,
            500
        };
    }
};

static CMainParams mainParams;

/**
 * Testnet (v1)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = -1;
        consensus.nMasternodePaymentsStartBlock = 121;
        consensus.nMasternodePaymentsIncreaseBlock = -1;
        consensus.nMasternodePaymentsIncreasePeriod = -1;
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 2282;
        consensus.nBudgetPaymentsCycleBlocks = 90;
        consensus.nBudgetPaymentsWindowBlocks = 39;
        consensus.nBudgetProposalEstablishingTime = 720;
        consensus.nSuperblockStartBlock = 2432;
        consensus.nSuperblockCycle = 90;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;

        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;

        consensus.nMajorityWindow = 390;
        consensus.BIP34Height = -1;
        consensus.BIP34Hash = uint256S("0x0");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 60;
        consensus.nPowTargetSpacing = 40;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 8;
        consensus.nMinerConfirmationWindow = 11;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1456790400;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800;

        pchMessageStart[0] = 0x4f;
        pchMessageStart[1] = 0xd1;
        pchMessageStart[2] = 0x6d;
        pchMessageStart[3] = 0xee;

        vAlertPubKey = ParseHex("042736aa94dcc46a596d1f42a5402261b6d9d8a72de40ace5a8856f9e5f7bab96f837f926a8ab8d1e2f8d6d7ef59732d99b55352c4fdf775bdb9690c42851609bd");
        nDefaultPort = 23200;
        nMaxTipAge = 0x7fffffff;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1517849983, 2442161, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock ==
               uint256S("0x00000ac3b982c0b616ae1a4188c1222c340979d3c69bdeffcd757c40037ef607"));
        assert(genesis.hashMerkleRoot ==
               uint256S("0x1799a2ff8e3776c2386f8b9b554da902a79e86072f48c8bf5c702f3c29c295e4"));

        vFixedSeeds.clear();
        vSeeds.clear();

        //vSeeds.push_back(CDNSSeedData("tnodes.aerisx.io", "tnodes.aerisx.io"));
        //vSeeds.push_back(CDNSSeedData("nodes.Aeris.org", "nodes.Aeris.org"));
        //vSeeds.push_back(CDNSSeedData("nodes.myaeriscoin.com", "nodes.myaeriscoin.com"));
        //vSeeds.push_back(CDNSSeedData("nodes.cryptophi.com", "nodes.cryptophi.com"));



        // Aeris addresses start with 'a'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        // Aeris script addresses start with 's'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 125);
        // Aeris private keys start with 'y' or '<'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 141);

        // Testnet Aeris BIP32 pubkeys
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(
                                             0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Aeris BIP32 prvkeys
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(
                                             0x94).convert_to_container<std::vector<unsigned char> >();

        // Testnet Aeris BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(
                                            0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5 * 60;
        strSporkPubKey = "04d2b954a7d4d5f69338cc41d59b59d2b022682b849272b8d0b354ea63cb9771493619ae3ecfc94719c05aeb2ac8f80ba1d546fe40562c5ce1de61089f5db4546d";
        strMasternodePaymentsPubKey = "04d2b954a7d4d5f69338cc41d59b59d2b022682b849272b8d0b354ea63cb9771493619ae3ecfc94719c05aeb2ac8f80ba1d546fe40562c5ce1de61089f5db4546d";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x00000ac3b982c0b616ae1a4188c1222c340979d3c69bdeffcd757c40037ef607")),
            1517849983,
            0,
            500
        };

    }
};

static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = -1;
        consensus.nMasternodePaymentsStartBlock = 121;
        consensus.nMasternodePaymentsIncreaseBlock = -1;
        consensus.nMasternodePaymentsIncreasePeriod = -1;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 212;
        consensus.nBudgetPaymentsCycleBlocks = 90;
        consensus.nBudgetPaymentsWindowBlocks = 39;
        consensus.nBudgetProposalEstablishingTime = 720;
        consensus.nSuperblockStartBlock = 318;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;

        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;

        consensus.BIP34Height = -1;
        consensus.BIP34Hash = uint256S("0x0");
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60;
        consensus.nPowTargetSpacing = 40;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108;
        consensus.nMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        pchMessageStart[0] = 0xe6;
        pchMessageStart[1] = 0xce;
        pchMessageStart[2] = 0xa3;
        pchMessageStart[3] = 0xba;
        nMaxTipAge = 1 * 60 * 60;
        nDefaultPort = 23300;
        nPruneAfterHeight = 1000;


        genesis = CreateGenesisBlock(1517849983, 2442161, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock ==
               uint256S("0x00000ac3b982c0b616ae1a4188c1222c340979d3c69bdeffcd757c40037ef607"));
        assert(genesis.hashMerkleRoot ==
               uint256S("0x1799a2ff8e3776c2386f8b9b554da902a79e86072f48c8bf5c702f3c29c295e4"));

        vFixedSeeds.clear();
        vSeeds.clear();

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5 * 60;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x00000ac3b982c0b616ae1a4188c1222c340979d3c69bdeffcd757c40037ef607")),
            1517849983,
            0,
            500
        };

        // Aeris addresses start with 'R'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 61);
        // Aeris script addresses start with 'U' or 'V'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 69);
        // Aeris private keys start with 'Q' or 'R'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 59);

        // Regtest Aeris BIP32 pubkeys start with
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(
                                             0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Aeris BIP32 prvkeys start with
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(
                                             0x94).convert_to_container<std::vector<unsigned char> >();

        // Regtest Aeris BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(
                                            0x01).convert_to_container<std::vector<unsigned char> >();
    }
};

static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(const std::string &chain) {
    if (chain == CBaseChainParams::MAIN)
        return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
        return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
        return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string &network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
