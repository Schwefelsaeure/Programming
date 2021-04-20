commit_authors=$(git shortlog --summary --numbered | cut --field=2)

echo "# Git Commits"
echo ""

echo "## Summary"
git shortlog --summary --numbered --email --no-merges --all

# echo "## Details"
# for commit_author in $commit_authors;
# do
#     echo "Commit author: $commit_author"
#     git log --author="$commit_author" --pretty=tformat: --numstat | awk '{ inserted+=$1; deleted+=$2; delta+=$1-$2; } END { printf "Commit stats:\n- Lines added (total)....  %s\n- Lines deleted (total)..  %s\n- Total lines (delta)....  %s\n", inserted, deleted, delta }' -
# done
