#!/bin/bash
set -e

# Update repository
echo "===== UPDATING LINUX REPOSITORY FOR ARCHITECTURE $2 ====== "
cd /var/telemetryjet-downloads/builds/cli/linux/$2/repo
cp "../telemetryjet-cli-linux_$2_$1.deb" $2
dpkg-sig -k telemetryjet --sign repo "$2/telemetryjet-cli-linux_$2_$1.deb"
apt-ftparchive packages $2 > Packages
gzip -k -f Packages
apt-ftparchive release . > Release
rm -fr Release.gpg;
gpg --default-key "TelemetryJet" -abs -o Release.gpg Release
rm -fr InRelease;
gpg --default-key "TelemetryJet" --clearsign -o InRelease Release
cd ..
sudo chown -R www-data:www-data *
sudo chmod -R 774 *
sudo chmod 774 *