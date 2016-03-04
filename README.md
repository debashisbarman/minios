# Mini OS 0.0.01
Mini Operating System is a educational operating system with monolithic kernel design and clean implementation for x86 machines, written in C and Assembly. It was born as an undergraduate project designed by [Debashis Barman](http://debashisbarman.github.io/). As the version (0.0.01) suggests this is not a mature product. Currently only a subset of AT hardwares is supported (screen, keyboard and serial lines). Memory management is done with the help of both segmentation and paging. Since the kernel alone leads to nowhere, a basic shell with some initial commands runs on the top of it.

##Tools
Before building the kernel, make sure that the following tools are available in your system.
<ul>
<li>An x86 computer (of course)</li>
<li>Linux</li>
<li>NASM assembler</li>
<li>gcc</li>
<li>ld (GNU Linker)</li>
<li>grub</li>
</ul>

##License
All the files in this repository are [MIT](http://opensource.org/licenses/MIT) licensed.

##Author
Debashis Barman ([http://www.debashisbarman.in](http://debashisbarman.github.io/))
