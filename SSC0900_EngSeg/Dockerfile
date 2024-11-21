# Use a base image with basic Linux tools
FROM debian:bullseye-slim

# Update and install dependencies
RUN apt-get update 
RUN apt-get install -y \
    curl \
    gnupg2 \
    software-properties-common \
    build-essential \
    libssl-dev \
    zlib1g-dev \
    net-tools

# Add the Metasploit GPG key and repository
RUN curl https://apt.metasploit.com/metasploit-framework.gpg.key | apt-key add - && \
    echo "deb https://apt.metasploit.com/ buster main" > /etc/apt/sources.list.d/metasploit-framework.list

# Update and install Metasploit Framework
RUN apt-get update && apt-get install -y metasploit-framework