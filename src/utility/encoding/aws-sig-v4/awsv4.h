#ifndef AWSV4_HPP
#define AWSV4_HPP

#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <ctime>
#include <iostream>
#include <sstream>
#include "openssl/sha.h"
#include "openssl/hmac.h"

namespace AWSV4 {
    const std::string ENDL{"\n"};
    const std::string STRING_TO_SIGN_ALGO{"AWS4-HMAC-SHA256"};
    const std::string AWS4{"AWS4"};
    const std::string AWS4_REQUEST{"aws4_request"};

    void sha256(const std::string str, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) noexcept;
    const std::string sha256_base16(const std::string) noexcept;

    const std::map<std::string,std::string> canonicalize_headers(const std::vector<std::string>& headers) noexcept;

    const std::string map_headers_string(const std::map<std::string,std::string>& header_key2val) noexcept;

    const std::string map_signed_headers(const std::map<std::string,std::string>& header_key2val) noexcept;

    const std::string canonicalize_request(const std::string& http_request_method,
                                           const std::string& canonical_uri,
                                           const std::string& canonical_query_string,
                                           const std::string& canonical_headers,
                                           const std::string& signed_headers,
                                           const std::string& hashed_payload) noexcept;

    const std::string string_to_sign(const std::string& algorithm,
                                     const std::string& timestamp,
                                     const std::string& credential_scope,
                                     const std::string& hashed_canonical_request) noexcept;
    const std::string sign(const std::string key, const std::string msg);

    const std::string credential_scope(const std::string datestamp,
                                       const std::string region,
                                       const std::string service,
                                       const std::string s) noexcept;

    const std::string calculate_signature(const std::string datestamp,
                                          const std::string secret,
                                          const std::string region,
                                          const std::string service,
                                          const std::string string_to_sign) noexcept;

}

#endif