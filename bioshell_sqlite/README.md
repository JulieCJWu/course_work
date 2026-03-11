# bioshell_sqlite

An interactive command-line shell for fetching, storing, and querying biological sequences from NCBI, backed by a local SQLite database.
Originally developed as coursework at UQAM (Autumn 2015), and optimized for HIV sequence analysis.

## Features

- Fetches GenBank records from NCBI by accession number and caches them locally
- Stores sequence metadata in a local SQLite database (`sequences.db`)
- Supports batch loading from a file of accession numbers
- Searches for sequence motifs across all stored sequences
- Displays per-sequence statistics (nucleotide/amino acid composition)
- Pre-loaded with HIV gene/protein reference data (`gag`, `pol`, `env`, `tat`, `rev`, `nef`, `vpr`, `vif`, `vpu`)

## Requirements

- Python 3
- [Biopython](https://biopython.org/) (`Bio`)
- SQLite3 (included in Python's standard library)

Install dependencies:
```bash
pip install biopython
```

## Usage

```bash
python bioShell3.py
```

### Shell Commands

| Command | Description |
|---|---|
| `help` | Show available commands |
| `list` | List all accession IDs stored in the database |
| `load <ID>` | Fetch a GenBank record from NCBI and store it (format: `AB123456`) |
| `loadmany <file>` | Batch load accession IDs from a text file (one ID per line) |
| `infos <ID>` | Display metadata and sequence statistics for an accession |
| `view <ID>` | Display the raw local GenBank file for an accession |
| `find <motif>` | Search for a motif (min. 5 bp) across all stored sequences |
| `remove <ID>` | Delete a sequence from the database |
| `exit` / `quit` | Exit the shell |

## Notes

- Sequences are saved as `.gb` files under a local `sequences/` directory.
- Only sequences under 10,000 bp are downloaded.
- Before running, set your email in `LoadSeqRecord()` as required by NCBI's Entrez API:
  ```python
  Entrez.email = "your.email@example.com"
  ```

## Author

Chao-Jung Wu — Autumn 2015
