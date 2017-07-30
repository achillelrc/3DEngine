#! /bin/sh

add_to_bashrc_if_not_exist()
{
	grep -q -F "$1" ~/.bashrc || echo "$1" >> ~/.bashrc
}

if [ -d ~/.graph_programming ];
then
	echo "Removing old .graph_programming folder"
	rm -rf ~/.graph_programming
fi

mkdir -p ~/.graph_programming/lib
mkdir -p ~/.graph_programming/include

echo "Copying development libraries."
cp -R -a lib/lib*.so* ~/.graph_programming/lib/.
echo "Copying header files."
cp -R include/* ~/.graph_programming/include/.

echo "Setting up environement variable."

echo "append_path_env_var()" >> ~/.bashrc
echo "{" >> ~/.bashrc
echo "	ENV_VAR=\`printenv \$1\`" >> ~/.bashrc
echo "	CONTENT=\$2" >> ~/.bashrc
echo "	if [[ ! -z \$ENV_VAR ]]" >> ~/.bashrc
echo "	then" >> ~/.bashrc
echo "			CONTENT=\$ENV_VAR:\${2}" >> ~/.bashrc
echo "	fi" >> ~/.bashrc
echo "	export \${1}=\$CONTENT" >> ~/.bashrc
echo "}" >> ~/.bashrc

add_to_bashrc_if_not_exist "### C Graphical Programming Environement Variable"
add_to_bashrc_if_not_exist "append_path_env_var \"LIBRARY_PATH\" \"${HOME}/.graph_programming/lib\""
add_to_bashrc_if_not_exist "append_path_env_var \"LD_LIBRARY_PATH\" \"${HOME}/.graph_programming/lib\""
add_to_bashrc_if_not_exist "append_path_env_var \"CPATH\" \"${HOME}/.graph_programming/include\""

echo
echo "Please execute: source ~/.bashrc"
